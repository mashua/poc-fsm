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

//    extern theState ( * const state_table[MAX_STATES+1][MAX_STATES+1])(void);    
    extern theState (* const state_trigger[MAX_STATES+1])(void);
    
    uint8_t from_state = STATE_1; /*Initial state to enter*/
    uint8_t to_state = from_state;
    
    while(1)
    {
        
        switch( to_state )
        {
            case STATE_1:
//                to_state = STATE_1;
                to_state = (*state_trigger[to_state])();
                break;
            case STATE_2:
//                to_state = STATE_2;
                to_state = (*state_trigger[to_state])();
                break;
            case STATE_3:
//                to_state = STATE_3;
                to_state = (*state_trigger[to_state])();
                break;
            case STATE_4:
//                to_state = STATE_4;
                to_state = (*state_trigger[to_state])();
                exit(0);
                break;
            default:
                printf("Erroneous state\n");
                exit(0);
                break;
        }
    }

//    while(1)
//    {
//        switch ( (*state_table[from_state][to_state])() )
//        {
//            case STATE_2:
//                from_state = STATE_2;
//                (*state_table[from_state][to_state])();
//                break;
//            default:
//                printf("Erroneus state\n");
//                break;
//        }
//    }
    
    return (EXIT_SUCCESS);
}

