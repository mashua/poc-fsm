#include "fsm.h"

/* The state / event lookup table, this is a table
 * that holds references to functions with no args */
theState (*state_table[MAX_STATES][MAX_EVENTS])(void) = {
    
        { actionVoid , actionVoid  }, /* zero padding */
        { actionS1_E1, actionS1_E2 }, /* state1 */
        { actionS2_E1, actionS2_E2 }, /* state2 */
        { actionS3_E1, actionS3_E2 }  /* state3 */
};

theState actionS1_E1(void){
    
    char *action = "S1";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
    return STATE_2;
}

theState actionS1_E2(void){
  
    char *action = "S2";
    char *event = "E2";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
}

theState actionS2_E1(void){
    
    char *action = "S2";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS2_E2(void){
    
}

theState actionS3_E1(void){
    
}

theState actionS3_E2(void){
    
}

theState actionVoid(void){
    
}