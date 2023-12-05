#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


bool    string_compare(char *str, char*cmp);
char    *get_line(char *buffer);
char    *create_null_term_buffer(size_t size);
void    *destroy_buffer( char* ptr);
size_t  file_size(FILE * fp);


#endif