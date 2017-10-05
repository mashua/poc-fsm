#ifndef FSM_H
#define FSM_H

//#define MAX_STATES LAST_STATE /*zero padding state + idle state + all other states*/
//#define MAX_EVENTS 1 /*the max. event number on any state*/

/* The states representation, */
typedef enum
{ 
    NO_STATE = 0, /*to be used as idle state also*/
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    LAST_STATE
} theState;

#define MAX_STATES LAST_STATE-1 /*MAX_STATES includes the range [NO_STATE - IDLE_STATE] or [0-6]*/

///* The events representation, */
//typedef enum
//{
//    NO_EVENT = 0,
//    EVENT_1,
//    EVENT_2,
//    EVENT_3,
//    EVENT_4,
//    EVENT_5,
//    LAST_EVENT
//} theEvent;

/* Function prototypes for action events */

theState trigger_S1(void);
//theState actionS1_E2(void);
//theState actionS1_E3(void);
//theState actionS1_E4(void);
//theState actionS1_E5(void);

theState trigger_S2(void);
//theState actionS2_E2(void);
//theState actionS2_E3(void);
//theState actionS2_E4(void);

theState trigger_S3(void);
//theState actionS3_E2(void);
//theState actionS3_E3(void);
//theState actionS3_E4(void);

theState trigger_S4(void);
//theState actionS4_E2(void);
//theState actionS4_E3(void);
//theState actionS4_E4(void);

theState go_to_void(void);

theState no_tran(void);

#endif /* FSM_H */

