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
    
    extern theState (*state_table)(void);
        
    printf("%d\n", MAX_STATES);
    
    theState test;
    
//    test = ((*state_table+3)+1)();
        
//    (*state_table[1][1])();
    
    if (trigger_S1() == STATE_2)
    {
        trigger_S2();
    }
    else
    {
        
    }

    trigger_S1();
    
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

