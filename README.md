#poc-fsm

A proof-of-concept Finite State Machine (FSM) implementation in ansi C and a code generation utility to construct the relevant .c and .h files needed to implement the described FSM. The representation of the states and the transitions between them is represented in a .tex file for easy visual inspection of your FSM. This .tex file is a totaly valid .tex document, and if you compile it by hand ( pdflatex <file>.tex ) then you should have a .pdf file of your FSM.
The state_parser.rb script parses that .tex file and produces a .yml file, in which later the same script uses to generate the .c and .h files.

**(read the <u>Future Work may be</u> section number 2, for very important info about the last/final state of your FSM)**

For the example implemented FSM see the attached poc-fsm.dia diagramm [1] and/or the poc-fsm.yml file, you can also compile a .pdf from the shipped .tex file [2]. The sample FSM has four states. The initial state is 'state1' and the transition are as follows:

  * From 'state1' you can go to 'state2', 'state3' and 'state4'.
  * From 'state2' you can go to 'state3' and 'state4'.
  * From 'state3' you can go to 'state1' and 'state4'
  * From 'state4' the only transition is the termination of the implementing process, so no transitions are described in the file, but an empty array ([]).

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

<u>**Currently Supported Features:**</u>

 1. Representation of the FSM in a yaml file (see shipped example poc-fsm.yml file).
 2. Parsing the .yml file and generation of one .h and one .c file. The .h file contains the definitions to be used, such as prototype functions, and a custom defined type for the states representation. The .c file contains skeleton code to implement your FSM transitioning logic. One function per defined state is generated with some facilities as: Documentation placeholder, logging of current triggered state and resulting state, and a Switch statement containig all possible next transitions for the specific state as they are described at the .yml file for the specific state. The generated skeleton functions are named trigger_<STATE_NAME\>, e.g, trigger_STATE6( );
 3. The generated files are stored on the 'code_gen' subfolder, relativelly from where the 'state_parser.rb' script is executed. You can change it by approprietally setting the ''FILE_GEN_DIR'' variable.

<u>**Future work may be:**</u>

1. A states validity table. The rows holds the 'From' state and column holds the 'To' state. The library user should be able to call stateValidity[2][1] == 1 to check if the transition from 'state2' to 'state1' is a valid one. Be aware that the array might have stateValidity[2][1] == 1 and stateValidity[1][2] == 0 or stateValidity[2][2] == 1, all of which represents perfectly valid transitions for a FSM. Zero padding for the array should be optional and enabled by default to avoid confusion to the programmer.

2. Currently the last state is not in the graph because adding a line like: "\path (state3) edge node {} (state3);" wouldn't make much sense at the generated pdf and also visualy destroys the final produced result. If you wanted generated either way (the code generator have a special case for it) you can add it by hand in the produced .yml file. The final state in the shipped example is represented by a node_name: State4 and nodes_to_go: [], which is an empty ruby array. See the shipped .yml file.

[1] To properly open, view and edit .dia files, you need the [Dia](http://live.gnome.org/Dia) program.

[2] To properly compile the .tex file into a .pdf you must have the 'pdflatex' command availiable and also the TikZ/pgf library.



