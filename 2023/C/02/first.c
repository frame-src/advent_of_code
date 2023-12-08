#include "../inc/utils.h"

FILE *f = NULL;

int value_per_line = 0;

bool valid_line(char *line){
    int i = 0;
    int tmp = 0;
    while(line[i]){
        if( isdigit(line[i])){
            tmp = atoi(&line[i]);
            if(tmp > 14)
                return false;
            while(isdigit(line[i]) != 0){
                i++;
            }
        }
        i++;
    }
    return true;
}

char **create_table(char *buffer)
{
    int i = 0;
    size_t counter = 0;
    char **table = malloc(sizeof(char*) * 1000);
    table[0] = get_line(&buffer[i]);
    printf("%s\n", table[0]);
    while(table[counter]) {
        i = i + strlen(table[counter]) + 1;
        counter++;
        table[counter] = get_line(&buffer[i]);
        // printf("%s\n", table[counter]);
    }
    table[counter] = NULL;
    i = 0;
    // printf("\n\nTEST\n\n");
    // while(table[i]){
    //     printf("%s\n", table[i]); i++;
    // }
    return table;
}

bool check_value( char c){
    if(c != '.'  && c != '\n' && c != '\0' && isdigit(c) == 0)
        return true;
    return false;
}

bool check_around(char **table, size_t x, size_t y){
    size_t tmp_x = 0;
    size_t tmp_y = 0;

    if(x !=0 && y != 0){
        tmp_x = x - 1;
        tmp_y = y - 1;
    } else if (x == 0 && y != 0){
        tmp_x = x;
        tmp_y = y - 1;
    } else if ( x != 0 && y == 0){
        tmp_x = x - 1;
        tmp_y = y;
    } else {
        tmp_x = x;
        tmp_y = y;
    }
    while(isdigit(table[y][x])){
        while(table[tmp_y][tmp_x] && tmp_x <= x + 1){
            while(table[tmp_y] && tmp_y <= y + 1){
                if(check_value(table[tmp_y][tmp_x]))
                    return true;
                tmp_y++;
            }
            if(y!=0)
                tmp_y = y -1;
            else
                tmp_y = y;
            tmp_x++;
        }
        x++;
    }
    return false;
}

void destroy_table(char **t){
    int i = 0;
    while(t[i]){
        free (t[i]);
        i++;
    }
    free (t);
}

void calculate_value(char **table){
    size_t y = 0;
    size_t x = 0;
    int sum = 0;
    while(table[y]){
        x = 0;
        while(table[y][x]){
            if(isdigit(table[y][x]) != 0 && check_around(table, x, y)){
                sum = sum + atoi(&table[y][x]);
                // printf("num:  %d \n", atoi(&table[y][x]));
                while(table[y][x] && isdigit(table[y][x]) != 0)
                    x++;
            } else {
                x++;
            }
            // printf("\n");
        }
        y++;
    }
    printf("%d", sum);
}


int main (void)
{
    char *buffer;
    size_t size = 0;
    char *line;
    
    f = fopen("../../input/02/input.txt", "r");
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
    char **table = create_table(buffer);
    calculate_value(table);
    destroy_table(table);
    return(0);
}