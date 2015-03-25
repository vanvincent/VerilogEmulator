/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/

#ifndef NET_H
#define NET_H
#include <vector>
#include <string>
using namespace std;

class Gate;

class Net {
 public:
  Net();
  Net(string n);
  ~Net();
  void addDriver(Gate *g);
  void addLoad(Gate *g);
  vector<Gate *> *getLoads();
  vector<Gate *> *getDrivers();
  string name();
  void setVal(char v);
  char computeVal();
  char getVal();
  void printDriversLoads();
  void computeDelay();
  int sort;
  int delay;
 private:
  vector<Gate *> *drivers;
  vector<Gate *> *loads;
  char val;
  string netname;
};
#endif
