#include "../inc/utils.h"

bool string_compare(char *str, char*cmp)
{
    size_t lenght = strlen(cmp);
    for (int i = 0; i < lenght; i++){
        if(str[i] != cmp[i])
            return false;
    }
    return true;
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

size_t file_size(FILE * fp)
{
    size_t counter = 0;
    
    while(fgetc(fp) != EOF){
         counter++;
    }
    return counter;
}