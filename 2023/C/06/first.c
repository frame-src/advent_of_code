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

void process_line(char *line){
    first_part(&line[0]);
    second_part(&line[5]);
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