/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "parse.h"
#include "design.h"
#include "gates.h"
#include "net.h"
#include "readsim.h"
#include<iomanip>

using namespace std;

int main (int argc, char* argv[])
{
	if (argc<4)
	{
		cerr<<"usage: ./gatesim verilog_filename sim_filename sim_result_filename"<<endl;
		return 1;
	}
	Design* module=parse(argv[1]);
	if (module!=NULL)
	{
		ofstream outfile;
		outfile.open("output.v");
		module->dump(outfile);
		outfile.close();
		cout<<"dump successful to output.v!"<<endl;
		vector<Net*>* netlist=module->all_nets();
		vector<Net*> sorted_netlist;
		//topdfs is a function that will perform a topological sort and generate a sorted netlist..
		topdfs(netlist,sorted_netlist);
		vector<Net*>::iterator it;
		vector<string> simlist;
		//a map that associates input_net's name with a vector of its value to be simulated
		map<string,vector<char> > simmap; 
		//readsim is a function that will read in the data from the .sim file and store them in both simlist and simmap
		int result = readsim(argv[2],simlist,simmap);
		if (result==0)
        	{
            		delete module;
            		return -1;
        	}

        	vector<string>::iterator it1;
        	vector<char>::iterator it2;

        	map<string,vector<char> >::iterator itm;
        	vector<Net*>* input_nets=module->get_pi_nets();
        	vector<Net*>* output_nets=module->get_po_nets();
        	map<string, Net*> dnet_map=module->get_net_map();
		//a map that associates output_net's name with a vector of its value after simulation
        	map<string,vector<char> > outputmap;
        	for (it=output_nets->begin();it!=output_nets->end();it++)
        	{
            		vector<char> values;
            		outputmap[(*it)->name()]=values;
        	}

        	int size=(simmap.begin()->second).size();
		//an overall loop that performs each simulation
        	for (int i=0;i<size;i++)
        	{
			//a loop that set value for the input nets based on the .sim file
            		for (vector<Net*>::iterator itv=input_nets->begin();itv!=input_nets->end();itv++)
            		{
                		char val=(simmap.find((*itv)->name()))->second[i];
                		(*itv)->setVal(val);
            		}
			//use the sorted netlist to compute each net's value and delay in a specific order
            		for(it=sorted_netlist.begin();it!=sorted_netlist.end();it++)
            		{
                		(*it)->computeVal();
                		(*it)->computeDelay();
            		}
			//store the final value for the every output net into the their respective vector in the outputmap
            		for (it=output_nets->begin();it!=output_nets->end();it++)
            		{
                		outputmap[(*it)->name()].push_back((*it)->getVal());
            		}
        	}


		ofstream out;
		out.open(argv[3]);
		//a loop that prints the names for each inputs
		for(it1=simlist.begin();it1!=simlist.end();it1++){
			out<<setw(5)<<*it1;
		}
		out<<" =>";
		//a loop that prints the names for each outputs
      		for(itm=outputmap.begin();itm!=outputmap.end();itm++){
			out<<setw(8)<<(itm->first);
		}
		out<<endl;
		//a loop that prints the values for each input and output for each simulation
		for(int k=0;k<size;k++){
			for(it1=simlist.begin();it1!=simlist.end();it1++){
				out<<setw(5)<<(simmap[*it1])[k];
			}
			out<<" =>";
			for(itm=outputmap.begin();itm!=outputmap.end();itm++){
			//for the purpose of better formatting 
			stringstream ss1,ss2;
			ss1<<(itm->second)[k];
			ss2<<dnet_map[itm->first]->delay;
			string result=ss1.str()+"@"+ss2.str();
			out<<setw(8)<<result;
			}
			out<<endl;
		}
		out.close();
		cout<<"simulation complete and results are typed in "<<argv[3]<<"!"<<endl;
		//delete all the dynamic allocated memories
		delete input_nets;
		delete output_nets;
		delete module;
	}
	return 0;
}
