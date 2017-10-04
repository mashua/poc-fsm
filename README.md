# poc-fsm

A proof-of-concept Finite State Machine (FSM) implementation in ansi C.

For the implemented FSM see the attached poc-fsm.dia diagramm. This sample FSM has four states. The initial state is 'state1' and the transition are as follows:

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
