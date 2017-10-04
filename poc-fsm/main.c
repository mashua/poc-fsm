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
//    extern theState (*state_table[MAX_STATES][MAX_EVENTS])(void);
    
    if (actionS1_E1() == STATE_2)
    {
        actionS2_E1();
    }
    else
    {
        actionS1_E2();
    }

    
    while(1)
    {
        
        /**/
//        from_to(  );
        switch (actionS1_E1())
        {
            case STATE_2:
                actionS2_E1();
                break;
            default:
                printf("Erroneus state\n");
                break;
        }
        
    }
    
    return (EXIT_SUCCESS);
}

