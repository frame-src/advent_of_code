#include "../inc/utils.h"

int main ( void ) {
    int time = 59707878;
    size_t distance = 430121812131276;

    size_t counter = 0;
    long int i = 0;
    long int s = 0;

    while(i < time){
        s = i * (time - i);
        if( s > distance)
            counter++;
        i++;
    }
    printf("Solution is %li", counter);
}
