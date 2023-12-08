#include "../../inc/utils.h"

FILE *f;
size_t size = 0;

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
    if(start)
        printf("%c",start);
    if(end)
        printf("%c", end);
    printf("\n");
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
    
    f = fopen("./test.txt", "r");
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
