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
    
    static theState currentState = IDLE_STATE;
        
//    printf("Event: %d\n", EVENT_1);
//    printf("State: %d\n", STATE_1);
    
    if (actionS1_E1() == STATE_2)
    {
        actionS2_E1();
    }
    else 
    {
        actionS1_E2();
    }
    
    
    return (EXIT_SUCCESS);
}

