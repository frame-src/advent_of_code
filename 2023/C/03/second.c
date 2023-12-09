#include "../inc/utils.h"
#define NUM_WINNING 10
#define NUM_OWNED 25
// #define NUM_WINNING 5
// #define NUM_OWNED 8
bool card[100];
int card_counter[300];

FILE *f = NULL;

void reset_card()
{
    for(int i = 0; i < 100; i++){
        card[i] = false;
    }
}
void reset_card_counter()
{
    for(int i = 0; i < 300; i++){
        card_counter[i] = 1;
    }
}

void set_card(int *owned){
    reset_card();
    printf("OWNED: ");
    for(int i = 0; i < NUM_OWNED; i++){
        printf("%d, ",owned[i]);
        card[owned[i]] = true;
    }
    printf("\n");
}

size_t calculate_point( int* winning){
    int counter = 0;
    printf("WINNING: ");
    for( int i = 0; i < NUM_WINNING; i++){
        printf("%d %s, ", winning[i], card[winning[i]]? "t" : "f");
        if(card[winning[i]] == true)
            counter ++;
    }
    return (counter);
}

int *create_winning(char*line, int *numbers){
    int pt = 0;
    for( int i = 0; i < NUM_WINNING; i++){
        while(line[pt] && isdigit(line[pt]) == 0)
            pt++;
        numbers[i] = atoi(&line[pt]);
        while(line[pt] && isdigit(line[pt]) != 0)
            pt++;
    }
    return(numbers);
}

int *create_owned(char*line, int *numbers){
    int pt = 0;
    for( int i = 0; i < NUM_OWNED; i++){
        while(line[pt] && isdigit(line[pt]) == 0)
            pt++;
        numbers[i] = atoi(&line[pt]);
        while(line[pt] && isdigit(line[pt]) != 0)
            pt++;
    }
    return (numbers);
}

void set_card_counter(size_t index, int duplicates){
    int multiplier = card_counter[index];
    for ( int i = 1; i <= duplicates; i++){
        if ( index + i < 300)
            card_counter[index + i] = card_counter[index + i] + (1 * multiplier);
    }
}

void process_point(char *line, size_t card_i)
{
    int *winning = malloc(sizeof(int) * NUM_WINNING );
    int *owned = malloc(sizeof(int) * NUM_OWNED );
        if(!winning || !owned)
            exit(1);
    int i = 0;
    while(line[i] != ':')
        i++;
    winning = create_winning(&line[++i], winning);
    while(line[i] != '|')
        i++;
    owned = create_owned(&line[++i], owned);
    set_card(owned);
    int duplicates = calculate_point(winning);
    set_card_counter(card_i, duplicates);
}

void calculate_value(char *buffer)
{
    size_t i = 0;
    size_t card_index = 0;
    size_t sum = 0;

    char *line = get_line(&buffer[i]);
    while(line) {
        process_point(line, card_index);
        i = i + strlen(line) + 1;
        destroy_buffer(line);
        line = get_line(&buffer[i]);
        card_index++;
    }
    printf("\n\n%li\n", card_index);
    for( i = 0; i < card_index; i++){
        sum = sum + card_counter[i];
        if(i%4 == 0)
            printf("\n");
        printf("i:%li\t\tv:%d | ",i, card_counter[i]);
    }
    printf("\nsum = %li", sum);
}

int main (void)
{
    char *buffer;
    size_t size = 0;
    char *line;
    
    f = fopen("../../input/03/input.txt", "r");
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
    reset_card_counter();
    calculate_value(buffer);
    return(0);
}