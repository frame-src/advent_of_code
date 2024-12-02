#include "../inc/utils.h"

FILE *f;
size_t size = 0;

int *process_line(char *str){
    int i = 0;
    int k = 0;
    int *value =malloc( sizeof(int) * 6);
    if( value == NULL)
        exit(1);
    while(str[i]){
        // while(!isnumber(str[i]))
        //     i++;
        value[k] = atoi(&str[i]);
        k++;
        while(isnumber(str[i]))
            i++;
        i++;
    }
    return value;
}

int calculate_value(int *vls, int max){
    int i = 0;
    int *new =malloc( sizeof(int) * max);
    if (!new)
        exit(1);
    while(i < max){
        new[i] = vls[i+1] - vls[i];
    }
    
    return (vls[max + new[i]])
}

void calc_solution(char *buffer)
{
    size_t i = 0;
    char *line = NULL;
    int ret_value = 0;
    line = get_line(&buffer[i]);
    int *value = process_line(line);
    ret_value = ret_value + calculate_value(value);
    while(line){
        i = i + strlen(line) + 1;
        line = destroy_buffer(line);
        line = get_line(&buffer[i]);
        free(value);
        value = process_line(line);
        ret_value = ret_value + calculate_value(value);
    }
    printf("%d\n", ret_value);
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

// test