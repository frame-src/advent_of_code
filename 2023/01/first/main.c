#include "../../inc/utils.h"

FILE *f = NULL;

#define CUBE_RED 12
#define CUBE_GREEN 13 
#define CUBE_BLUE 14

bool valid_line(char *line){
    int i = 0;
    int tmp = 0;
    printf("line:  %s  \t is: ", line);
    while(line[i]){
        if( isdigit(line[i])){
            tmp = atoi(&line[i]);
            if(tmp > 14)
                return false;
            while(isdigit(line[i]) != 0){
                i++;
            }
        }
        if(line[i] == 'g' || line[i] == 'r' || line[i] == 'b'){
            if(line[i] == 'g' && tmp > CUBE_GREEN)
                return false;
            else if(line[i] == 'b' && tmp > CUBE_BLUE)
                return false;
            else if(line[i] == 'r' && tmp > CUBE_RED)
                return false;      
            tmp = 0;
        }
        i++;
    }
    return true;
}

void calc_solution(char *buffer)
{
    int i = 0;
    size_t counter = 1;
    size_t sum = 0;

    char *line = get_line(&buffer[i]);
    while(line) {
        if(valid_line(&line[7])){
            printf("Valid!\n");
            sum = sum + counter;
        } else 
            printf("Not Valid!\n");
        counter++;
        i = i + strlen(line) + 1;
        destroy_buffer(line);
        line = get_line(&buffer[i]);
    }
    printf("SUM: %li", sum);
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