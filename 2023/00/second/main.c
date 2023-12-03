#include "../utils/utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


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
bool string_compare(char *str, char*cmp)
{
    size_t lenght = strlen(cmp);
    for (int i = 0; i < lenght; i++){
        if(str[i] != cmp[i])
            return false;
    }
    return true;
}

// one two tree four five six seven eight nine 
char is_a_number(char *str, char c)
{
    char num = '\0';
    switch (c){
        case 'o':
            if(string_compare(str, "one"))
                num = '1';
            break;
        case 't':
            if(string_compare(str, "two"))
                num = '2';
            else if (string_compare(str, "three"))
                num = '3';
            break;
        case 'f':
            if(string_compare(str, "four"))
                num = '4';
            else if ( string_compare(str, "five"))
                num = '5';
            break;
        case 's':
            if(string_compare(str,"six"))
                num = '6';
            if(string_compare(str,"seven"))
                num = '7';
            break;
        case 'e':
            if(string_compare(str,"eight"))
                num = '8';
            break;
        case 'n':
            if(string_compare(str,"nine"))
                num = '9';
            break;
    }
    return num;
}

size_t process_line(char* line)
{
    size_t i = 0;
    char start = '\0';
    char end = '\0';
    size_t res = 0;

    while(line[i]){
        if( !start && isdigit(line[i]))
           start = line[i];
        else if( isdigit(line[i]))
           end = line[i]; 
        char tmp_start = is_a_number(&line[i],line[i]);
        if(tmp_start){
            if(!start)
                start = tmp_start;
            else
                end = tmp_start;
        }
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
