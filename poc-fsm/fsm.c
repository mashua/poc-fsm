#include "fsm.h"

static theStates currentState = NO_STATE;

/*The state / event lookup table, this is a table
 *that holds references to functions with no args*/
void (* state_table[MAX_STATES][MAX_EVENTS])(void) = {
    
    { actionVoid , actionVoid  },
    { actionS1_E1, actionS1_E2 }, /* procedures for state 1 */
    { actionS2_E1, actionS2_E2 }, /* procedures for state 2 */
    { actionS3_E1, actionS3_E2 }  /* procedures for state 3 */
};

void actionS1_E1(void){
    
}

void actionS1_E2(void){
    
}

void actionS2_E1(void){
    
}

void actionS2_E2(void){
    
}

void actionS3_E1(void){
    
}

void actionS3_E2(void){
    
}

void actionVoid(void){
    
}
