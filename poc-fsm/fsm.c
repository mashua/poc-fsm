#include "fsm.h"

/* The state / event lookup table, this is a table
 * that holds references to functions with no args
 * which returns theState types*/
theState (*state_table[MAX_STATES][MAX_EVENTS])(void) = {
                    /*events that can occur in the specific state*/
/*zeropadevents*/   { 0xFF , 0xFF, 0xFF, 0xFF },
/*state1 events*/   { idle_state_e1, idle_state_e2, idle_state_e3, idle_state_e4, idle_state_e5 },
/*state2 events*/   { actionS1_E1, actionS1_E2, actionS1_E3, actionS1_E4},
/*state3 events*/   { actionS2_E1, actionS2_E2, actionS2_E3, actionS2_E4},
/*state4 events*/   { actionS3_E1, actionS3_E2, actionS3_E3, actionS3_E4} 
}; 

theState idle_state_e1(void){
    
    char *action = "IDLE STATE";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    return STATE_1;
}

theState idle_state_e2(void){
    
    char *action = "IDLE STATE";
    char *event = "E2";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    return STATE_1;
}

theState idle_state_e3(void){
    
    char *action = "IDLE STATE";
    char *event = "E3";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    return STATE_1;
}

theState idle_state_e4(void){
    
    char *action = "IDLE STATE";
    char *event = "E4";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    return STATE_1;
}

theState idle_state_e5(void){
    
    char *action = "IDLE STATE";
    char *event = "E5";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    return STATE_1;
}

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

theState actionS1_E3(void){
  
    char *action = "S1";
    char *event = "E3";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
}

theState actionS1_E4(void){
  
    char *action = "S1";
    char *event = "E4";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
    
}

theState actionS2_E1(void){
    
    char *action = "S2";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS2_E2(void){
    
    char *action = "S2";
    char *event = "E2";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS2_E3(void){
    
    char *action = "S2";
    char *event = "E3";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS2_E4(void){
    
    char *action = "S2";
    char *event = "E4";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS3_E1(void){
    
    char *action = "S3";
    char *event = "E1";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS3_E2(void){
    
    char *action = "S3";
    char *event = "E2";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS3_E3(void){
    
    char *action = "S3";
    char *event = "E3";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionS3_E4(void){
    
    char *action = "S3";
    char *event = "E4";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}

theState actionVoid(void){
    
    char *action = "VOID";
    char *event = "NOEVENT";
    printf("IN ACTION: %s, AND EVENT: %s\n", action, event);
}