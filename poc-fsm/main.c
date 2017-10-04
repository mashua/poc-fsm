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
    
    if (triggerS1() == STATE_2)
    {
        triggerS2();
    }
    else
    {
        
    }

    triggerS1();
    
    while(1)
    {
        /**/
        switch (triggerS1())
        {
            case STATE_2:
                triggerS2();
                break;
            default:
                printf("Erroneus state\n");
                break;
        }
    }
    
    return (EXIT_SUCCESS);
}

