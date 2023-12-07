#include "../inc/utils.h"
#define NUM_WINNING 10
#define NUM_OWNED 25
// #define NUM_WINNING 5
// #define NUM_OWNED 8
bool card[100];

FILE *f = NULL;

void reset_card()
{
    for(int i = 0; i < 100; i++){
        card[i] = false;
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
    printf("\n");
    if(counter == 0){
        printf("POINT: V: 0 C: %d\n", counter);
        return 0;
    }
    size_t return_value = 1;
    for(int i = 1; i < counter; i++)
        return_value = return_value * 2;
    printf("POINT: V: %li C: %d\n", return_value, counter);
    return (return_value);
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

size_t process_point(char *line)
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
    return(calculate_point(winning));
}

void calculate_value(char *buffer)
{
    int i = 0;
    size_t sum = 0;

    char *line = get_line(&buffer[i]);
    printf("\n_______________________________________________________________________________________________________________________________________________________________________\n%s\n",line);
    while(line) {
        sum = sum + process_point(line);
        i = i + strlen(line) + 1;
        destroy_buffer(line);
        line = get_line(&buffer[i]);
        printf("\n_______________________________________________________________________________________________________________________________________________________________________\n%s\n",line);
    }
    printf("sum = %li", sum);
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
    calculate_value(buffer);
    return(0);
}