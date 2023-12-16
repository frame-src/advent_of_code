#include "../inc/utils.h"

FILE *f = NULL;
char cards_seed[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

struct card_info{
    char   *hand;
    int    rank;
    size_t value;
};

enum hand_type{
    HIGHEST_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

enum hand_type calculate_value(size_t value, size_t counter){
    if(counter == 4)
        return FOUR_OF_A_KIND;
    else if (counter == 5)
        return FIVE_OF_A_KIND;
    else {
        if (value == 0)
            return HIGHEST_CARD;
        else if (value == 2)
            return ONE_PAIR;
        else if (value == 3)
            return THREE_OF_A_KIND;
        else if (value == 4)
            return TWO_PAIR;
        else if (value == 5)
            return FULL_HOUSE;
    }
}

struct card_info *check_hand(struct card_info *ci){
    size_t i,j, counter;
    char trio = '\0';
    char duo = '\0';
    size_t value;

    i = j = counter = 0;
    while(cards_seed[i]){
        while(ci->hand[j]){
            if(cards_seed[i] == ci->hand[j])
                counter++;
            j++;
        }
        if(counter == 2 || counter == 3)
            value = value + counter;
        if (counter == 4 || counter == 5){
            ci->value = calculate_value(value, counter);
            return;
        }
        counter = 0;
        j = 0;
        i++;
    }

}

size_t *seeds = NULL;
struct info **conversion_table = NULL;
bool CONVERTING = false;

void print(){
    int i = 0;
    while(conversion_table && conversion_table[i]){
        i++;
    }
}

void debug(){
    printf("debug\n");
}


size_t *add_value_to_nmbrs(size_t *n, size_t value){
    int size = 0;
    int i = 0;
    printf("valeu = %li\n",value);
    if(value == 135215567)
        printf("%li\n",n[1]);
    if(n == NULL){
        ;    
    } else {
        while(n[i]!= -1){
            i++;
        }
    }
    size = i + 2;
    size_t *new = malloc( sizeof(size_t) * size);
    if(!new)
        exit (1);
    new[i + 1] = -1;
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

size_t min_sort(){
    int i = 0;
    size_t min = seeds[0];
    while(seeds[i]){
        if(seeds[i] < min){
            min = seeds[i];
            i = 0;
        }
        i++;
    }
    return min;
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
    printf("%li",min_sort());
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