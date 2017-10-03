#ifndef FSM_H
#define FSM_H

#define MAX_STATES 4
#define MAX_EVENTS 4

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
theState actionS1_E1(void);
theState actionS1_E2(void);
theState actionS2_E1(void);
theState actionS2_E2(void);
theState actionS3_E1(void);
theState actionS3_E2(void);
theState actionVoid(void);

#endif /* FSM_H */

