#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "fsm.h"

/* The state transition lookup table, this is a table
 * that holds references to functions with no args
 * which returns theState types.
 * Usage in the form of (*state_table[2][1])(); means trigger the 2 state
 * that 'should' land on state 1.
 */
theState ( * const state_table[MAX_STATES+1][MAX_STATES+1])(void) =
{
                /*zeropad col*/ /*TO state no*/
                            /*0*/    /*1*/       /*2*/       /*3*/        /*4*/
/*zeropad row*/         {  no_tran, no_tran,    no_tran,    no_tran,    no_tran    },
/*FROM state no: 1*/    {  no_tran, no_tran,    trigger_S1, trigger_S1, trigger_S1 },
/*FROM state no: 2*/    {  no_tran, no_tran,    no_tran,    trigger_S2, trigger_S2 },
/*FROM state no: 3*/    {  no_tran, trigger_S3, no_tran,    no_tran,    trigger_S3 },
/*FROM state no: 4*/    {  no_tran, no_tran,    no_tran,    no_tran,    no_tran    }
};

/* This table contains the validity between the states.
 * if( stateValidity[from_state_no][to_state_no] == 0 ) then
 * its not a valid state transition.
 */
uint8_t stateValidity[MAX_STATES+1][MAX_STATES+1] = {
                /*zeropad*/    /*state no*/
                  /*0*/    /*1*/    /*2*/    /*3*/    /*4*/
/*zeropad*/        {0,       0,       0,       0,       0 },
/*state no: 1*/    {0,       0,       1,       1,       1 }, /*go from state 1 to state 2*/
/*state no: 2*/    {0,       0,       0,       1,       1 },
/*state no: 3*/    {0,       1,       0,       0,       1 }, /*go from state 3 to state 2*/
/*state no: 4*/    {0,       0,       0,       0,       0 }    
};

theState no_tran(void){
    
    char *action = "VOID";
    char *event = "NOEVENT";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
    return NO_STATE;
}

theState trigger_S1(void){
    
    char *current_state = "STATE1";
    printf("ACTION: %s, TRIGGERED\n", current_state);
    
    /*here you can do whatever you must to go to the next possible states
     *we simply go random to one of the possible next states
     */
    uint8_t go_to_state = 4;
    srand(50);
    go_to_state = rand() % (MAX_STATES);
    
    switch(go_to_state)
    {
        case STATE_2:
            return STATE_2;
        case STATE_3:
            return STATE_3;
        case STATE_4:
            return STATE_4;
        default:
            return STATE_4;
    }
}

theState trigger_S2(void){
    
    char *current_state = "STATE2";
    printf("ACTION: %s, TRIGGERED\n", current_state);
        
    uint8_t go_to_state = 4;
    srand(50);
    go_to_state = rand() % ( MAX_STATES + 1 - 1);
    
    switch(go_to_state)
    {
        case STATE_3:
            return STATE_3;
        case STATE_4:
            return STATE_4;
        default:
            return STATE_4;
    }
}

theState trigger_S3(void){
    
    char *current_state = "STATE2";
    printf("ACTION: %s, TRIGGERED\n", current_state);
    
    uint8_t go_to_state = 4;
    srand(50);
    go_to_state = rand() % ( MAX_STATES + 1 - 1);
    
    switch(go_to_state)
    {
        case STATE_1:
            return STATE_1;
        case STATE_4:
            return STATE_4;
        default:
            return STATE_4;
    }
}

theState trigger_S4(void){
    
    char *current_state = "STATE2";
    printf("ACTION: %s, TRIGGERED\n", current_state);
    
    return NO_STATE;
}
