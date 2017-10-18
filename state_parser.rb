require 'psych'
require 'yaml'

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

 states="";
 functions="";
 header_file= <<SECTION1
#ifndef FSM_H
#define FSM_H

SECTION1
 
 header_file+= <<SECTION2
/* The states representation, */
typedef enum
{ 
  NO_STATE = 0,
SECTION2

 #build the states enum contents
 states_array.each{ |elem|
   states+="\t"+elem.to_s;
   states+=",\n";
 }
 header_file+=states;
 
 header_file+= <<SECTION3
  LAST_STATE
} theState;

/*MAX_STATES includes the range [NO_STATE - IDLE_STATE] or [0-6]*/
#define MAX_STATES LAST_STATE-1
SECTION3
 
 header_file+= <<SECTION4

/* Function prototypes for triggering states */

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

#include "fsm.h"
SECTION1
 
 implementation_file+= <<SECTION2
/* This table holds references to functions that triggers the states.
 * The zero indexed function is 'no_tran' and is used to have one to one
 * mapping between the trigger functions and the array indexes.
 */
theState (* const state_trigger[MAX_STATES+1])(void) = {
         no_tran,
SECTION2
 
 #build the function pointers for the upper array
 states_array.each_index { |elem_index|
   states+=" "+states_array[elem_index].to_s;
   #don't put an extra ',' on the last array element
   unless elem_index == states_array.length()-1
     states+=",";
   end                                            
 }
 implementation_file+=states+="\n};";
 
 #build trigger_<> function bodies
 states_hash.each{ |key, array_val |
   functions+= "\ntheState trigger_#{key}(void){\n\n";
   functions+="\tchar *current_state = \"#{key}\";\n";
   functions+="\tprintf(\"ACTION: %s, TRIGGERED\\n\", current_state);"; #escape the \n
   functions+="\n\tuint8_t go_to_state = #{array_val.last}\n";
   functions+="\n\t/*here you can do whatever you must to go to the next possible states*/";
   functions+="\n\t/*go_to_state = */\n";
   functions+="\n\tswitch(go_to_state)";
   functions+="\n\t{";
   
   array_val.each{ |elem|
     functions+="\n\t\tcase #{elem}:\n\t\t\treturn #{elem};";
   }   
   functions+="\n\t\tdefault:\n\t\t\treturn #{array_val.last};\n\t}";
   functions+="\n}\n";
 }
 
 puts functions;

 # puts  implementation_file;
end


if ARGV.length() == 0 then
  printf("Missing .yml file to parse state graph input from\n");
  exit(0);
else
  printf("Using file:#{ARGV[0]} to parse the state graph and produce .c and .h files.\n");
  begin
    temp_graph = YAML::load_file(ARGV[0]);
  rescue Psych::SyntaxError
    puts "Invalid .yml file, exiting, plese conform to the shipped example or use the API to create the .yml file from ruby code.\n";
    exit(-1);
  end  
  states_hash = Hash.new();
  states_arr = Array.new();
  #temp_graph is an array containing StateNode objects.
  temp_graph.each do |elem|
    puts "Now examing #{elem.node_name}...\n";
    temp_arr = Array.new();
    elem.nodes_to_go.each do |inner_elem|
      temp_arr << inner_elem;
    end
    states_hash.store("#{elem.node_name}",temp_arr);
    states_arr<<elem.node_name;
  end
#  return_header_file_template(states_arr);
   return_implementation_file_template(states_arr,states_hash);

#  puts states_hash;
  exit(0);
end

#---------------------------------------------------------------------------
# api usage for your reference, in order to create the .yml spec by code
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
