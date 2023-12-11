#include "../inc/utils.h"

FILE *f = NULL;

struct info{
    size_t destination_start;
    size_t source_start;
    size_t range;
};

int *seeds = NULL;
struct info **conversion_table = NULL;
bool CONVERTING = false;

int *add_value_to_nmbrs(int *n, int value){
    int size = 0;
    int i = 0;

    if(n == NULL){
        size = 2;    
    } else {
        while(n[i] != -1)
            i++;
        size = i + 1;
    }
    int *new = malloc( sizeof(int) * size);
    if(new == NULL)
        exit (1);
    i = 0;
    while(n && n[i] != -1){
        new[i] = n[i];
        i++;
    } 
    new[i] = value;
    new[i + 1] = -1;
    return new;
}

void update_conversion_table(int *nmbrs){
    int i = 0;
    int size = 2;
    while(conversion_table && conversion_table[i])
        i++;
    size = size + i;
    struct info **new = malloc (sizeof(struct info) * (size));
    if(!new)
        exit(1);
    if(conversion_table){
        for(i = 0; i < size - 1; i++){
            new[i]->destination_start = conversion_table[i]->destination_start;
            new[i]->source_start = conversion_table[i]->source_start;
            new[i]->range = conversion_table[i]->range;
            free(conversion_table[i]);
        }
        free(conversion_table);
    }
    new[i]->destination_start = nmbrs[0];
    new[i]->source_start = nmbrs[1];
    new[i]->range = nmbrs[3];
    i++;
    new[i] = NULL;
    conversion_table = new;
}

void manage_conversion_table(char* line){
    size_t i = 0;
    int value = 0;
    int *nmbrs = NULL;

    while(line[i]){
        while(!isnumber(line[i]))
            i++;
        value = atoi(&line[i]);
        nmbrs = add_value_to_nmbrs(nmbrs, value);
        while(isnumber(line[i]))
            i++;
        printf("TEST2\n");
    }
    if(!seeds){
        seeds = nmbrs;
        return;
    } 
    update_conversion_table(nmbrs);
    free(nmbrs);
}

size_t convert(int seed){
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
        seed = seed - conversion_table[i]->source_start;
        new_value = conversion_table[i]->destination_start + seed;
    }
    else 
        new_value = seed;
    return new_value;
}

void perform_conversion(){
    size_t i = 0 ;

    if(conversion_table){
        while(seeds[i]){
            seeds[i] = convert(seeds[i]);
            i++;
        }
    }
}

void process_line(char *line){
    if(isalpha(line[0])){
        CONVERTING = true;
        printf("TEST0\n");
        return;
    }
    else if(line[0] == '\n'){
        perform_conversion();
        CONVERTING = false;
        printf("TEST1\n");
        return;
    } else {
        manage_conversion_table(line);
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
        printf("%i",seeds[i]);
        i++;
    }
}

int main (void)
{
    char *buffer;
    size_t size = 0;
    char *line;
    
    f = fopen("../../input/04/test.txt", "r");
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