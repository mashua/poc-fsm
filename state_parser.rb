#!/usr/bin/ruby

require 'psych'
require 'yaml'

FILE_GEN_DIR = "code_gen";

class StateNode

  #The name of the node.  
  attr_accessor :node_name;
  #Array that holds the names of the visiting nodes, from the current node.
  attr_accessor :nodes_to_go;
  
  def initialize(the_state_name)

    self.node_name = the_state_name.to_s;
    self.nodes_to_go = Array.new();
  end
  
  def add_visiting_node(the_state_name)

    self.nodes_to_go << the_state_name.to_s;
  end
end#class def ends here

#The heredoc 'template' for the header file code gen.
def return_header_file_template(states_array)

#  max_states_len = 0;
 # states_array.each{ |elem|
  #  unless elem.length < max_states_len
  #}
 
 states="";
 functions="";
 header_file= <<SECTION1
#ifndef FSM_H
#define FSM_H

SECTION1
 
 header_file+= <<SECTION2
#define MAX_STATE_LEN = #{6}

/* The states representation, */
typedef enum
{
\tNO_STATE = 0,
SECTION2

 #build the states enum contents
 states_array.each{ |elem|
   states+="\t"+elem.to_s;
   states+=",\n";
 }
 header_file+=states;
 
 header_file+= <<SECTION3
\tLAST_STATE
} theState;

/*MAX_STATES includes the range [NO_STATE - IDLE_STATE] or [0-6]*/
#define MAX_STATES LAST_STATE-1
SECTION3
 
 header_file+= <<SECTION4

/* Function prototypes for triggering states */

/**
*
* Function to handle a no valid transition.
* Also used for zero padding the states array.
* @return
*/
theState no_tran(void);

SECTION4

 states_array.each{ |elem|
   functions+="/**\n * Function to trigger state #{elem}.\n * @return\n */\n theState trigger_#{elem}(void);\n\n";
 }
 header_file+=functions;
 header_file+="#endif /*FSM_H*/"; 
 header_file;
end

#The heredoc 'template' for the implementation (.c) file code gen.
def return_implementation_file_template(states_array, states_hash)

 states="";
 functions="";
 implementation_file= <<SECTION1
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fsm.h"

SECTION1
 
 implementation_file+= <<SECTION2
/* This table holds references to functions that triggers the states.
 * The zero indexed function is 'no_tran' and is used to have one to one
 * mapping between the trigger functions and the array indexes.
 */
theState (* const state_trigger[MAX_STATES+1])(void) = {\n\tno_tran, /* no_tran function used for zero padding */
SECTION2

 #build the function pointers for the upper array
 states_array.each_index { |elem_index|
   states+="\ttrigger_"+"#{states_array[elem_index]}"
   #don't put an extra ',' on the last array element, although that later C standards hava added support for it.
   unless elem_index == states_array.length()-1
     states+=",";
   end
}

# implementation_file+=states+="\n};\n";
 states+="\n};\n\n";
 #build the states name array       

   
 states+="static char *state_names[] = {\n\t\"ZP\", /* used for zero padding */\n\t";
 
 states_array.each_index { |elem_index|
   states+="\"#{states_array[elem_index]}\" "
   #don't put an extra ',' on the last array element, although that later C standards hava added support for it.
   unless elem_index == states_array.length()-1
     states+=",";
   end
}
 states+="\n};\n";
 implementation_file+=states;
 
 #build the no_tran function
 functions+= "\ntheState no_tran(void){\n\n";
 functions+="\tchar *current_state = \"NO_TRAN_STATE\";\n";
 functions+="\tprintf(\"ACTION: %s, TRIGGERED\\n\", current_state);"; #escape the \n
 functions+="\n\t/*you have entered a non-valid state of the graph. Something weird has happened.*/";
# functions+="\n\texit(0);";
 functions+="\n}\n";
 
 #build trigger_<> function bodies
 states_hash.each{ |key, array_val |
   if key.eql?(states_array.last) then
     functions+= "\ntheState trigger_#{key}(void){\n\n";
     functions+="\tchar *current_state = \"#{key}\";\n";
     functions+="\tprintf(\"STATE: %s, TRIGGERED\\n\", current_state);"; #escape the \n
     functions+="\n\t/*you have entered the last state of the graph.There is nowhere to go from here.*/";
     functions+="\n\texit(0);";
     functions+="\n}\n";     
   else
     functions+= "\ntheState trigger_#{key}(void){\n\n";
#     functions+="\tchar *current_state = \"#{key}\";\n";
     functions+="\tchar *current_state = (char*)malloc(sizeof(char)*#{key.length});\n";
     functions+="\tstrcpy(current_state, \"#{key}\");\n";
     functions+="\tprintf(\"STATE: %s, TRIGGERED\\n\", current_state);"; #escape the \n
     functions+="\n\tuint8_t go_to_state = #{array_val.last};\n";
     functions+="\n\t/*here you can do whatever you must to go to the next possible states*/";
     functions+="\n\t/*go_to_state = */\n";
     
     functions+="\n\tstrcpy(current_state, state_names[go_to_state]);"
     functions+="\n\tprintf(\"GOING TO: %s \\n\", current_state);";
     functions+="\n\tfree(current_state);";
     functions+="\n\treturn go_to_state;";
     functions+="\n}\n";
#     functions+="\n\tswitch(go_to_state)";
#     functions+="\n\t{";   
#     array_val.each{ |elem|
#       functions+="\n\t\tcase #{elem}:";
#       functions+="\n\t\t\tstrcpy(current_state,\"#{elem}\");"
#       functions+="\n\t\t\tprintf(\"GOING TO: %s \\n\", current_state);";
#       functions+="\n\t\t\tfree(current_state);";
#       functions+="\n\t\t\treturn #{elem};";
#     };
#     functions+="\n\t\tdefault:";
#     functions+="\n\t\t\tstrcpy(current_state,\"#{array_val.last}\");"
#     functions+="\n\t\t\tprintf(\"GOING TO: %s \\n\", current_state);"
#     functions+="\n\t\t\treturn #{array_val.last};\n\t}";
#     functions+="\n}\n";
   end
 }
  
 implementation_file+=functions;
 implementation_file;
end

#The heredoc 'template' for sample main code file code gen.
def return_sample_main_file_template(states_array, states_hash)

 states="";
 functions="";
 sample_main_code= <<SECTION1
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "fsm.h"

SECTION1
 
 sample_main_code+= <<SECTION2
/* This is sample code to copy in your main.c file.
 * The template code enters the first state as configured by your .yml file, 
 * and calls the relevant trigger_ function.
 */
extern theState (* const state_trigger[MAX_STATES+1])(void);\n
int main(int argc, char** argv) {\n
SECTION2

# sample_main_code+= "\tuint8_t from_state = #{states_array[0]};\n";

 sample_main_code+= <<SECTION3
\tuint8_t go_to_state = #{states_array[0]};\n
\twhile(1)\n\t{
\t\tswitch(go_to_state)
\t\t{
SECTION3
 
 #build trigger_<> function bodies
 states_hash.each{ |key, array_val|
   
#     array_val.each{ |elem|
       functions+="\t\t\tcase #{key}:\n";
       functions+="\t\t\t\tgo_to_state = (*state_trigger[go_to_state])();\n"
       functions+="\t\t\t\tbreak;\n"
 #    };
#     functions+="\n\t\t\t\tstrcpy(current_state,\"#{array_val.last}\");"
 #    functions+="\n\t\t\t\tprintf(\"GOING TO: %s \\n\", current_state);"
  #   functions+="\n\t\t\t\treturn #{array_val.last};\n\t}";
 }

 functions+="\t\t\tdefault:\n";
 functions+="\t\t\t\tprintf(\"Erroneous State\\n\");\n";
 functions+="\t\t\t\texit(-1);\n";
 functions+="\t\t}/*switch case ends here*/";
 functions+="\n\t}/*while loop ends here*/";
 functions+="\n}";
 sample_main_code+=functions;
 sample_main_code;
end

#Parses .tex file containing the graph representation.
#Matches (<node_names>) in lines containing "\path" text lines
#Returns the a hash of the graph, where the hash keys are the
#starting nodes and each key value is an array of the visiting nodes.
def parse_tex_file()

  reg = /\(([^()]+)\)/;#regex to match the \path lines to extract the nodes info.
  t = File.open("poc-fsm.tex","r");
  graph_hash = Hash.new();
  
  t.each_line{ |line_text|
    if(line_text.to_s.match(/.*?(path)/) != nil) then
      #i'm on a text line that contains \path tikz tex code.
     #match data is in form [["node1"],["node2"]]
     match_data = line_text.scan(reg);
     if( graph_hash.key?(match_data[0][0])) then
       #node as a key exists
       temp = graph_hash[match_data[0][0]];
       temp << match_data[1][0];
       graph_hash.store(match_data[0][0], temp);
     elsif
       #key does not exist       
       graph_hash.store(match_data[0][0], Array.new());
       unless match_data[0][0].to_s.eql?(match_data[1][0]) #the same state name in source and destination.
         graph_hash.store(match_data[0][0], graph_hash[match_data[0][0]] << match_data[1][0] );
       end
     end
    end
 }
 graph_hash;
end

#Accepts the graph represented in a hash an
#converts it to a .yml file.
def create_yaml_repr(the_graph_hash)

  nodes_array = Array.new();
  #For each key, create a StateNode object
  #and for each values add visiting nodes to the StateNode object
  the_graph_hash.keys.each{ |key|

    temp_state_node = StateNode.new(key);
    nodes_array << temp_state_node;
    the_graph_hash[key].each{ |visiting_node|
      temp_state_node.add_visiting_node(visiting_node);
    }    
  }
  dump_file(nodes_array.to_yaml, "poc-fsm.yml");
end

def dump_file(the_file_content, filename)
  
  file = File.new(filename,"w");
  file.write(the_file_content.to_s);
  file.flush();
  file.close();
end

if ARGV.length() == 0 then
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
  printf("\nMissing .tex or .yml file to parse state graph info.\n");
  printf("Usage is like:\n");
  printf("\t'ruby state_parser.rb' <states_file.tex>\n");
  printf("or:\n");
  printf("\t'ruby state_parser.rb' <states_file.yml>\n");
  printf("~exited(-1):\n");
  exit(-1);
else
#  printf("Using file:#{ARGV[0]} to parse the state graph and produce the .yml .c and .h files.\n");
#  printf("Files will be generated at #{Dir.pwd.concat("/").concat(FILE_GEN_DIR)} directory\n");
  if ARGV[0].to_s.match(/\.tex/) != nil then
  #
    graph = parse_tex_file();
    create_yaml_repr(graph);
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\npoc-fsm.yml file generated, inspect it as nesessary, or now run \n'ruby state_parser.rb poc-fsm.yml' to generate the driving code for your FSM.\n");
    printf("~exited(0):\n");
    exit(0);
  elsif ARGV[0].to_s.match(/\.yml/) != nil
  #
    begin
      temp_graph = YAML::load_file(ARGV[0]);
    rescue Psych::SyntaxError
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
      printf("\nInvalid .yml file, exiting, plese conform to the shipped example \nor use the API to create the .yml file from ruby code.\n");
      printf("~exited(-1):\n");
      exit(-1);
    end
    states_hash = Hash.new();
    states_arr = Array.new();
    #temp_graph is an array containing StateNode objects.
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    temp_graph.each do |elem|
      printf("\nNow examing #{elem.node_name}...");
      temp_arr = Array.new();
      elem.nodes_to_go.each do |inner_elem|
        temp_arr << inner_elem;
      end
      states_hash.store("#{elem.node_name}",temp_arr);
      states_arr<<elem.node_name;
    end
    begin
      unless Dir.exist?(File.join(Dir.pwd, FILE_GEN_DIR))
        Dir.mkdir(File.join(Dir.pwd, FILE_GEN_DIR), 0777);
      end
      fsmc = File.new(File.join(Dir.pwd, FILE_GEN_DIR, "fsm.c"), "w");
      fsmc.write(return_implementation_file_template(states_arr,states_hash).to_s);
      fsmc.flush();
      fsmc.close();    
      fsmh = File.new(File.join(Dir.pwd, FILE_GEN_DIR, "fsm.h"), "w");
      fsmh.write(return_header_file_template(states_arr));
      fsmh.flush();
      fsmh.close();
      samplemainc = File.new(File.join(Dir.pwd, FILE_GEN_DIR, "samplemain.c"), "w");
      samplemainc.write(return_sample_main_file_template(states_arr,states_hash).to_s);
      samplemainc.flush();
      samplemainc.close();
      printf("Finish examining states and generating code.\n");
      printf("Check 'code_gen' directory for the generated code.\n");      
    rescue Exception => ex
      puts ex;
      raise();
    ensure
      #nothing
    end   
  else
    raise Exception.new("Out of this world error");
    exit(-1);
  end
  #bye!
  exit(0);
end

#---------------------------------------------------------------------------
# api usage for your reference, in order to create the .yml spec by code
# and then parsi it from this script
#---------------------------------------------------------------------------
poc_fsm = Array.new();

state1 = StateNode.new("State1");
state1.add_visiting_node("State2");
state1.add_visiting_node("State3");
state1.add_visiting_node("State4");

state2 = StateNode.new("State2");
state2.add_visiting_node("State3");
state2.add_visiting_node("State4");

state3 = StateNode.new("State3");
state3.add_visiting_node("State1");
state3.add_visiting_node("State4");

#this is the last state from where you are not trancending to nowhere.
#it is represented by an empty array in the .yml file.
state4 = StateNode.new("State4");

poc_fsm << state1;
poc_fsm << state2;
poc_fsm << state3;
poc_fsm << state4;

yaml_file = File.new("poc-fsm.yml","w" );

yaml_file.write(poc_fsm.to_yaml);
yaml_file.close();

puts poc_fsm.to_yaml;
#----------------------------------------------------------------------------
