/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/

#ifndef DESIGN_H
#define DESIGN_H
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include "gates.h"
#include "net.h"

using namespace std;


class Design {
 public:
  Design();
  Design(string n);
  ~Design();
  string name();
  void add_pi(string n);
  void add_po(string n);
  Net *find_net(string net_name);
  Gate *find_gate(string inst_name);
  Net* add_find_net(string n);
  Gate* add_find_gate(int gtype, string n, int delay);
  vector<Net *> *get_pi_nets();
  vector<Net *> *get_po_nets();
  vector<Net *> *get_wire_nets();
  vector<Net *> *all_nets();
  vector<Gate *> *all_gates();
  map<string,Net*> get_net_map();
  void dump(ostream &os);
 private:
  string desname;
  map<string, Net *> design_nets;
  map<string, Gate *> design_gates;
  vector<string> pis;
  vector<string> pos;

};

#endif
