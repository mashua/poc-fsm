# poc-fsm

A proof-of-concept Finite State Machine (FSM) implementation in ansi C and a code generation utility to construct the relevant .c and .h files needed to implement the described FSM. The representation of the states and the transitions between them is represented in yaml (.yml) file.

For the example implemented FSM see the attached poc-fsm.dia diagramm [1] and/or the poc-fsm.yml file. The sample FSM has four states. The initial state is 'state1' and the transition are as follows:

  * From 'state1' you can go to 'state2', 'state3' and 'state4'.
  * From 'state2' you can go to 'state3' and 'state4'.
  * From 'state3' you can go to 'state1' and 'state4'
  * From 'state4' the only transition is the termination of the implementing process, so no transitions are described in the file, but an emtpy array ([]).

An ASCII representation of the nodes and transitions is the following:

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

( <u>Underlined</u> means not yet implemented )

Currently Supported Features: 

 1. Representation of the FSM in a yaml file (see shipped example poc-fsm.yml file).
 2. Parsing the .yml file and generation of one .h and one .c file. The .h file contains the definitions to be used, such as prototype functions, and a custom defined type for the states representation. The .c file contains skeleton code to implement your FSM transitioning logic. One function per defined state is generated with some facilities as: Documentation placeholder, logging of current triggered state and resulting state, and a Switch statement containig all possible next transitions for the specific state as they are described at the .yml file for the specific state. The generated skeleton functions are named trigger_<STATE_NAME\>, e.g, trigger_STATE6( );

Supported Features: 

<u> 1. A states validity table. The rows holds the 'From' state and column holds the 'To' state. The library user should be able to call stateValidity[2][1] == 1 to check if the transition from 'state2' to 'state1' is a valid one. Be aware that the array might have stateValidity[2][1] == 1 and stateValidity[1][2] == 0 or stateValidity[2][2] == 1, all of which represents perfectly valid transitions for a FSM. Zero padding for the array should be optional and enabled by default to avoid confusion to the programmer.</u>
 
<u> 2. A 'theState' enumeration (typedefed) to be used as returned type from functions that drives the FSM, so this return type will be the next state that the FSM will come to.</u>

    3. D

[1]* To properly open, view and edit .dia files, you need the [Dia](http://live.gnome.org/Dia) program.



