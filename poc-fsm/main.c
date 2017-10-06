/* 
 * File:   main.c
 * Author: mashua
 *
 * Created on September 1, 2017, 4:45 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "fsm.h"

int main(int argc, char** argv) {

    static theState currentState = NO_STATE;
    
    extern theState ( * const state_table[MAX_STATES+1][MAX_STATES+1])(void);
        
    printf("%d\n", MAX_STATES);
    
    theState test;
        
    test = (*state_table[1][2])();
    
    while(1)
    {
        /**/
        switch (trigger_S1())
        {
            case STATE_2:
                trigger_S2();
                break;
            default:
                printf("Erroneus state\n");
                break;
        }
    }
    
    return (EXIT_SUCCESS);
}

