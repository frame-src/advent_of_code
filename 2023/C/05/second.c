#include "../inc/utils.h"

int main ( void ) {
    // int time = 59707878;
    int time = 71530;
    // size_t distance = 430121812131276;
    size_t distance = 940200;

    size_t counter = 0;
    int i,s = 0;

    while(i <= time){
        s = i * (time - i);
        if( s > distance)
            counter++;
        i++;
    }
    printf("Solution %li", counter);
}
