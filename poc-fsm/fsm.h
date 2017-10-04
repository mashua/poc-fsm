#ifndef FSM_H
#define FSM_H

#define MAX_STATES 5 /*zero padding state + idle state + all other states*/
#define MAX_EVENTS 1 /*the max. event number on any state*/

/* The states representation, */
typedef enum
{ 
    NO_STATE = 0,    
    STATE_1,
    STATE_2, 
    STATE_3, 
    STATE_4, 
    STATE_5,
    IDLE_STATE
} theState;

/* The events representation, */
typedef enum
{
    NO_EVENT = 0,
    EVENT_1,
    EVENT_2,
    EVENT_3,
    EVENT_4,
    EVENT_5
} theEvent;

/* Function prototypes for action events */

theState triggerS1(void);
//theState actionS1_E2(void);
//theState actionS1_E3(void);
//theState actionS1_E4(void);
//theState actionS1_E5(void);

theState triggerS2(void);
//theState actionS2_E2(void);
//theState actionS2_E3(void);
//theState actionS2_E4(void);

theState triggerS3(void);
//theState actionS3_E2(void);
//theState actionS3_E3(void);
//theState actionS3_E4(void);

theState triggerS4(void);
//theState actionS4_E2(void);
//theState actionS4_E3(void);
//theState actionS4_E4(void);

theState triggerVoid(void);

#endif /* FSM_H */

