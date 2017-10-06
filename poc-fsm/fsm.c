#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "fsm.h"

///* The state / event lookup table, this is a table
// * that holds references to functions with no args
// * which returns theState types*/
//theState (*state_table[MAX_STATES][MAX_EVENTS])(void) = {
//                    /*events that can occur in the specific state*/
///*zeropadevents*/   { triggerVoid , triggerVoid, triggerVoid, triggerVoid, triggerVoid },
///*state1 events*/   { triggerS1, actionS1_E2, actionS1_E3, actionS1_E4, actionS1_E5},
///*state2 events*/   { triggerS1, actionS1_E2, actionS1_E3, actionS1_E4, triggerVoid },
///*state3 events*/   { triggerS2, actionS2_E2, actionS2_E3, actionS2_E4, triggerVoid },
///*state4 events*/   { triggerS3, actionS3_E2, actionS3_E3, actionS3_E4, triggerVoid }
//};

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
/*state no: 1*/    {0,       0,       1,       1,       1 },   /*go from state 1 to state 2*/
/*state no: 2*/    {0,       0,       0,       1,       1 },
/*state no: 3*/    {0,       1,       0,       0,       1 },    /*go from state 3 to state 2*/
/*state no: 4*/    {0,       0,       0,       0,       0 }    
};

theState no_tran(void){
    
    return NO_STATE;
}

theState trigger_S1(void){
    
    char *action = "S1";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
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

//theState actionS1_E2(void){
//  
//    char *action = "S2";
//    char *event = "E2";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//    
//}
//
//theState actionS1_E3(void){
//  
//    char *action = "S1";
//    char *event = "E3";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//    
//}
//
//theState actionS1_E4(void){
//  
//    char *action = "S1";
//    char *event = "E4";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//    
//}
//
//theState actionS1_E5(void){
//  
//    char *action = "S1";
//    char *event = "E5";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//    
//}

theState trigger_S2(void){
    
    char *action = "S2";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
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

//theState actionS2_E2(void){
//    
//    char *action = "S2";
//    char *event = "E2";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}
//
//theState actionS2_E3(void){
//    
//    char *action = "S2";
//    char *event = "E3";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}
//
//theState actionS2_E4(void){
//    
//    char *action = "S2";
//    char *event = "E4";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}

theState trigger_S3(void){
    
    char *action = "S3";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
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

//theState actionS3_E2(void){
//    
//    char *action = "S3";
//    char *event = "E2";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}
//
//theState actionS3_E3(void){
//    
//    char *action = "S3";
//    char *event = "E3";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}
//
//theState actionS3_E4(void){
//    
//    char *action = "S3";
//    char *event = "E4";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}

theState trigger_S4(void){
    
    char *action = "S3";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
    return NO_STATE;
}

//theState actionS4_E2(void){
//    
//    char *action = "S3";
//    char *event = "E2";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}
//
//theState actionS4_E3(void){
//    
//    char *action = "S4";
//    char *event = "E3";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}
//
//theState actionS4_E4(void){
//    
//    char *action = "S4";
//    char *event = "E4";
//    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
//}

theState go_to_void(void){
    
    char *action = "VOID";
    char *event = "NOEVENT";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}