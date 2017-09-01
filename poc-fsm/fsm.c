#include "fsm.h"


/* The state / event lookup table, this is a table
 * that holds references to functions with no args */
theState (*state_table[MAX_STATES][MAX_EVENTS])(void) = {
    
    { actionVoid , actionVoid  }, /* zero padding */
    { actionS1_E1, actionS1_E2 }, /* procedures for state 1 */
    { actionS2_E1, actionS2_E2 }, /* procedures for state 2 */
    { actionS3_E1, actionS3_E2 }  /* procedures for state 3 */
};

theState actionS1_E1(void){
    
    
}

theState actionS1_E2(void){
    
}

theState actionS2_E1(void){
    
}

theState actionS2_E2(void){
    
}

theState actionS3_E1(void){
    
}

theState actionS3_E2(void){
    
}

theState actionVoid(void){
    
}
