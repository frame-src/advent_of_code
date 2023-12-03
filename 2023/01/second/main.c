#include "../../inc/utils.h"

FILE *f = NULL;

#define CUBE_RED 12
#define CUBE_GREEN 13 
#define CUBE_BLUE 14

int valid_line(char *line){
    int i = 0;
    int tmp = 0;
    int red,green,blue;

    red = green = blue = 0;
    while(line[i]){
        if( isdigit(line[i])){
            tmp = atoi(&line[i]);
            while(isdigit(line[i]) != 0){
                i++;
            }
        }
        if(line[i] == 'g' || line[i] == 'r' || line[i] == 'b'){
            if(line[i] == 'g' && tmp > green)
                green = tmp;
            else if(line[i] == 'b' && tmp > blue)
                blue = tmp;
            else if(line[i] == 'r' && tmp > red)
                red = tmp;      
            tmp = 0;
        }
        i++;
    }
    printf("green %d red %d blue %d \n", green, red, blue);
    return green * red * blue;
}

void calc_solution(char *buffer)
{
    int i = 0;
    size_t sum = 0;

    char *line = get_line(&buffer[i]);
    while(line) {
        sum = sum + valid_line(&line[7]);
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