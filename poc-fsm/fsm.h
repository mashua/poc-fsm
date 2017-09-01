#ifndef FSM_H
#define FSM_H

#define MAX_STATES 4
#define MAX_EVENTS 4

/*The states representation,*/
typedef enum states { NO_STATE = 0, STATE_1, STATE_2, STATE_3, STATE_4, STATE_5 } theStates;

/*The events representation,*/
typedef enum events { NO_EVENT = 0, EVENT_1, EVENT_2, EVENT_3, EVENT_4, EVENT_5 } theEvents;

/*Function prototypes for action events*/
void actionS1_E1(void);
void actionS1_E2(void);
void actionS2_E1(void);
void actionS2_E2(void);
void actionS3_E1(void);
void actionS3_E2(void);
void actionVoid(void);

#endif /* FSM_H */

