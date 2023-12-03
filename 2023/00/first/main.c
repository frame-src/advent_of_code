#include "../utils/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *f;
size_t size = 0;

size_t file_size(FILE * fp)
{
    size_t counter = 0;
    
    while(fgetc(fp) != EOF){
         counter++;
    }
    return counter;
}

char *create_null_term_buffer(size_t size)
{
    char *buffer;

    buffer = malloc(1 + (size * sizeof(char)));
    if(buffer == NULL)
          exit (1);
    buffer[size] = '\0';
    return buffer;
}

void *destroy_buffer( char* ptr)
{
    free(ptr);
    return NULL;
}

char *get_line(char *buffer)
{
    size_t i = 0;
    char *nl = NULL;

    while(buffer[i]){
        if(buffer[i] == '\n'){
            nl = create_null_term_buffer(i);
            for(int iter = 0; iter < i; iter++){
                nl[iter] = buffer[iter];
            }
            nl[i] = '\0';
            return nl;
        }
        i++;
    }
    return NULL;
}

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
    
    f = fopen("input.txt", "r");
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
