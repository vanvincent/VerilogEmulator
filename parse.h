/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include "design.h"
#include "gates.h"
#include "net.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
using namespace std;

//a function that will return a pointer to a Design if the .v file contains no grammar error; otherwise, returns NULL
Design* parse(char *);

string detect_input(string,set<string>&); //a helper function that will detect inputs and if successful, put them in a set 
string detect_output(string,set<string>&);//a helper function that will detect outputs and if successful, put them in a set
string detect_wire(string,set<string>&);//a helper function that will detect wires and if successful, put them in a set
//a helper function that will detect gates and sotre their individual port lists if no errors are found
string detect_gates(string,int&,int&,set<string>&,set<string>&,vector<string>&);
string detect_module(string,set<string>&);//a helper function that will simply detect the "module" line of a Verilog file
bool detect_end(string);  //a helper function that will simply detect the "endmodule" line 
bool detect_blank(string); //a helper function that will check for an empty line
bool detect_comment(string); //a helper function that will check for a comment line
void topdfs(vector<Net *> * ,vector<Net *>&); //a function that will perform a topological sort on all the nets of a design
void dfs(Net*,vector<Net *>&);  //a recursive function that is used in topdfs
