#include "../inc/utils.h"

FILE *f = NULL;

struct info{
    size_t destination_start;
    size_t source_start;
    size_t range;
};

size_t *seeds = NULL;
struct info **conversion_table = NULL;
bool CONVERTING = false;

size_t *add_value_to_nmbrs(size_t *n, size_t value){
    int size = 0;
    int i = 0;

    if(n == NULL){
        size = 2;    
    } else {
        while(n[i] != -1)
            i++;
        size = i + 1;
    }
    size_t *new = malloc( sizeof(size_t) * size);
    if(!new)
        exit (1);
    new[i] = -1;
    i = 0;
    while(n && n[i] != -1){
        new[i] = n[i];
        i++;
    } 
    new[i] = value;
    return new;
}

void update_conversion_table(size_t *nmbrs){
    int i = 0;
    int size = 2;
    while(conversion_table && conversion_table[i])
        i++;
    size = size + i;
    struct info **new = malloc (sizeof(struct info *) * (size));
    if(!new)
        exit(1);
    if(conversion_table){
        for(i = 0; i < size - 2; i++){
            new[i] = malloc(sizeof(struct info ));
            if (!new[i])
                exit(1);
            new[i]->destination_start = conversion_table[i]->destination_start;
            new[i]->source_start = conversion_table[i]->source_start;
            new[i]->range = conversion_table[i]->range;
            free(conversion_table[i]);
        }
        free(conversion_table);
    }
    new[i] = malloc(sizeof(struct info ) * 1);
    if (!new[i])
        exit(1);
    new[i]->destination_start = nmbrs[0];
    new[i]->source_start = nmbrs[1];
    new[i]->range = nmbrs[2];
    new[i + 1] = NULL;
    conversion_table = new;
}

void fill_conversion_table(char* line){
    size_t i = 0;
    size_t value = 0;
    size_t *nmbrs = NULL;

    while(line[i]){
        while(line[i] && !isnumber(line[i]))
            i++;
        value = atol(&line[i]);
        nmbrs = add_value_to_nmbrs(nmbrs, value);
        while(isnumber(line[i]))
            i++;
    }
    if(!seeds){
        seeds = nmbrs;
        return;
    }
    update_conversion_table(nmbrs);
    free(nmbrs);
}

size_t convert(size_t seed){
    size_t i = 0;
    size_t upper_bound = 0;
    size_t new_value = 0;
    bool check = false;
    while(conversion_table[i]){
        upper_bound = conversion_table[i]->source_start + conversion_table[i]->range;
        if(conversion_table[i]->source_start <= seed && seed < upper_bound){
            check = true;
            break;
        }
        i++;
    }
    if(check == true){
        size_t diff = seed - conversion_table[i]->source_start;
        new_value = conversion_table[i]->destination_start + diff;
    }
    else 
        new_value = seed;
    return new_value;
}

void perform_conversion(){
    size_t i = 0 ;
    if(conversion_table){
        while(seeds[i] > 0){
            seeds[i] = convert(seeds[i]);
            i++;
        }
    }
}

void clean_conversion_table(){
    int i = 0;
    
    if( conversion_table){
        while( conversion_table[i]){
            free( conversion_table[i]);
            i++;
        }
        free(conversion_table);
        conversion_table = NULL;
    }
}

void print(){
    int i = 0;
    while(conversion_table && conversion_table[i]){
        i++;
    }
}

void debug(){
    printf("debug\n");
}

void process_line(char *line){
    if(isalpha(line[0])){
        clean_conversion_table();
        CONVERTING = true;
        return;
    }
    else if(line[0] == '\n' || line[0] == '\0'){
        perform_conversion();
        CONVERTING = false;
        return;
    } else {
        fill_conversion_table(line);
    }
}

void calculate_value(char *buffer)
{
    int i = 0;

    char *line = get_line(&buffer[i]);
    while(line) {
        process_line(line);
        i = i + strlen(line) + 1;
        destroy_buffer(line);
        line = get_line(&buffer[i]);
    }
    i = 0;
    while(seeds[i]){
        printf("%i ",seeds[i]);
        i++;
    }
}

int main (void)
{
    char *buffer;
    size_t size = 0;
    char *line;
    
    f = fopen("../../input/04/input.txt", "r");
    if (f == NULL)
        exit(1);
    size = file_size(f);
    buffer = create_null_term_buffer(size);
    rewind(f);
    size = fread(buffer,sizeof(char),size,f);
    if (feof(f))
        printf("Error: unexpected end of file\n");
    else if (ferror(f))
        perror("Error reading file\n");
    calculate_value(buffer);
    return(0);
}