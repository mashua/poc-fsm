#ifndef FSM_H
#define FSM_H

#define MAX_STATES 4 /*idle state + all other states*/
#define MAX_EVENTS 5 /*the max. event number on any state*/

/* The states representation, */
typedef enum
{ 
    NO_STATE = 0,
    IDLE_STATE,
    STATE_1,
    STATE_2, 
    STATE_3, 
    STATE_4, 
    STATE_5
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

theState idle_state_e1(void);
theState idle_state_e2(void);
theState idle_state_e3(void);
theState idle_state_e4(void);
theState idle_state_e5(void);

theState actionS1_E1(void);
theState actionS1_E2(void);
theState actionS1_E3(void);
theState actionS1_E4(void);

theState actionS2_E1(void);
theState actionS2_E2(void);
theState actionS2_E3(void);
theState actionS2_E4(void);

theState actionS3_E1(void);
theState actionS3_E2(void);
theState actionS3_E3(void);
theState actionS3_E4(void);

theState actionVoid(void);

#endif /* FSM_H */

