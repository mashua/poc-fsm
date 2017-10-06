#ifndef FSM_H
#define FSM_H

/* The states representation, */
typedef enum
{ 
    NO_STATE = 0,
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    LAST_STATE
} theState;

/*MAX_STATES includes the range [NO_STATE - IDLE_STATE] or [0-6]*/
#define MAX_STATES LAST_STATE-1

/* Function prototypes for triggering states */

/**
 * Function to handle a no valid transition.
 * @return 
 */
theState no_tran(void);

/**
 * Function to trigger state 1.
 * @return 
 */
theState trigger_S1(void);

/**
 * Function to trigger state 2.
 * @return 
 */
theState trigger_S2(void);

/**
 * Function to trigger state 3.
 * @return 
 */
theState trigger_S3(void);

/**
 * Function to trigger state 4.
 * @return 
 */
theState trigger_S4(void);

#endif /* FSM_H */

