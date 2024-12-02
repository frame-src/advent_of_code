#include "../inc/utils.h"

FILE *f;
size_t size = 0;

size_t process_line(char* line){
    size_t i = 0;
    char start = '\0';
    char end = '\0';
    size_t res = 0;

    while(line[i]){
        if( !start && isdigit(line[i]))
           start = line[i];
        else if( isdigit(line[i]))
           end = line[i]; 
        i++;
    }
    if(start)
        res = (start - '0') * 10;
    if(end)
        res = res + (end - '0');
    else
        res = res + start - '0';
    return (res);
}

void calc_solution(char *buffer)
{
    size_t i = 0;
    size_t sum = 0;
    char *line = NULL;
    
    line = get_line(&buffer[i]);
    while(line){
        sum = sum + process_line(line);
        i = i + strlen(line) + 1;
        line = destroy_buffer(line);
        line = get_line(&buffer[i]);
    }
    printf("%li", sum);
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
