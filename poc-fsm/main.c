/* 
 * File:   main.c
 * Author: mashua
 *
 * Created on September 1, 2017, 4:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "fsm.h"

int main(int argc, char** argv) {

    static theState currentState = NO_STATE;
    
    extern theState ( * const state_table[MAX_STATES+1][MAX_STATES+1])(void);
        
    printf("%d\n", MAX_STATES);
    uint8_t from_state = 1;
    uint8_t to_state = 2;
    
    while(1)
    {
        switch ( (*state_table[from_state][to_state])() )
        {
            case STATE_2:
                from_state = STATE_2;
                (*state_table[from_state][to_state])();
                break;
            default:
                printf("Erroneus state\n");
                break;
        }
    }
    
    return (EXIT_SUCCESS);
}

