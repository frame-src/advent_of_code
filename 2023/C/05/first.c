#include "../inc/utils.h"

int main ( void ) {
    int time[7] = {7,15,30,59,70,78,78};
    int distance[7] = {9,40,200,430, 1218, 1213, 1276};

    int counter = 0;
    int j,i,s = 0;
    int sol = 1;
    bool inf = false;

    while(j < 7){
        while(i < time[j]){
            s = i * (time[j] - i);
            if( s > distance[j]){
                counter++;
                inf = true; 
            }
            if ( s <= distance[j] && inf == true)
                break;
            i++;
        }
        printf("Counter: %d\n", counter);
        sol = sol * counter;
        if(j == 2){
            printf("TEST: \tSolution = %d\n", sol);
            sol = 1;
        }
        i = 0;
        inf = false;
        counter = 0;
        j++;
    }
    printf("INPUT: \tSolution = %d", sol);
}