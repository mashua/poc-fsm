# poc-fsm

A proof-of-concept Finite State Machine (FSM) implementation in ansi C.

For the implemented FSM see the attached poc-fsm.dia diagramm. The sample FSM has four states. The initial state is 'state1' and the transition are as follows:

  * From 'state1' you can go to 'state2', 'state3' and 'state4'.
  * From 'state2' you can go to 'state3' and 'state4'.
  * From 'state3' you can go to 'state1' and 'state4'
  * From 'state4' the only transition the termination of the implementing process.

An ASCII representation of the nodes and transitions can be the following:

***
    +------+
    |state1|
    +------+
       | ^
       | |    +------+
       | |    |state2|
       | |    +------+    
       | |       ^ |   +------+
       | |       | |-->|state3|
       | |       | |   +------+
       | |       | |    | ^  |  +------+
       | |       | |    | |  |  |state4|
       | |       | |    | |  |  +------+
       | |       | |    | |  |    ^ ^ 
       | |       | |____|_|__|____| |
       | |       |      | |         |
       | |_______|______| |         |
       |         |        |         |
       |         |        |         |
       |_________|________|_________|
***

( <u>Underlined</u> means NOT IMPLEMENTED YET )

So for each of these states we create the following:

<u> 1. A states validity table. The rows holds the 'From' state and column holds the 'To' state. The library user should be able to call stateValidity[2][1] == 1 to check if the transition from 'state2' to 'state1' is a valid one. Be aware that the array might have stateValidity[2][1] == 1 and stateValidity[1][2] == 0 or stateValidity[2][2] == 1, all of which represents perfectly valid transitions for a FSM. Zero padding for the array should be optional and enabled by default to avoid confusion to the programmer.</u>
 
<u> 2. A 'theState' enumeration (typedefed) to be used as returned type from functions that drives the FSM, so this return type will be the next state that the FSM will come to.</u>

