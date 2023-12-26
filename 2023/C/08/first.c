#include "../inc/utils.h"

FILE *f;
size_t size = 0;


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
        process_line(line);
    }
    count_step();
}

int main (void)
{
    char *buffer;
    size_t size = 0;
    char *line;
    
    f = fopen("/Users/francesco/Documents/advent_of_code/2023/input/08/test.txt", "r");
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
