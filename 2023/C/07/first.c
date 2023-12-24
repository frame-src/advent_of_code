#include "../inc/utils.h"

FILE *f;
size_t size = 0;
int map[212122][2];
char *instruction;

void count_step()
{
    int count, i, next;
    count = i = next = 0;
    while(instruction[i]){
        if(instruction[i] == 'L')
            next = map[next][0];
        else if ( instruction[i] == 'R')
            next = map[next][0];
        if(next == 212121)
            break;
        i++;
        count ++;
        if(!instruction[i])
            i == 0;
    }
    printf("%d", count);
}

void init_instruction(char *line)
{
    int size = strlen(line);
    instruction = malloc(size * sizeof(char) + 1);
    if( instruction == NULL)
        exit(1);
    int i = 0;
    while(line[i]){
        instruction[i] = line[i];
        i++;
    }
    instruction[i] = '\0';
}

int convert_to_index(char *str)
{
    int index;
    index = index + (str[0] - 'A')* 10000;
    index = index + (str[1] - 'A')* 100;
    index = index + (str[2] - 'A');
    return index;
}

void process_line(char* line)
{
    if(!isupper(line[0]))
        return;
    map[convert_to_index(&line[0])][0] = convert_to_index(&line[7]);
    map[convert_to_index(&line[0])][0] = convert_to_index(&line[12]);
}

void calc_solution(char *buffer)
{
    size_t i = 0;
    char *line = NULL;
    
    line = get_line(&buffer[i]);
    init_instruction(line);
    while(line){
        i = i + strlen(line) + 1;
        line = destroy_buffer(line);
        line = get_line(&buffer[i]);
        process_line(&line[i]);
    }
    count_step();
}

int main (void)
{
    char *buffer;
    size_t size = 0;
    char *line;
    
    f = fopen("./Users/francesco/Documents/advent_of_code/2023/input/00/input.txt", "r");
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
    calc_solution(buffer);
    destroy_buffer(buffer);
    return(0);
}
