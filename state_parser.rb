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

if ARGV.length() == 0 then
  printf("Missing .yml file to parse input from\n");
  exit(-1);
else
  printf("Using file:#{ARGV[0]} to parse the state graph and produce .c and .h files.\n");
  temp_graph = YAML::load_file(ARGV[0]);
  #temp_graph is an array containing StateNode objects.
  temp_graph.each do |elem|
    puts elem.to_yaml
  end
  #puts temp_graph[1].to_yaml

  exit(-1);
end

#-----------------------------------------------------------------------
# api usage for your reference.
#-----------------------------------------------------------------------
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
#-----------------------------------------------------------------------
