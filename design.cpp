/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include <ostream>
#include <map>
#include <string>
#include <vector>
#include "gates.h"
#include "net.h"
#include "design.h"

using namespace std;

Design::Design(){}
Design::Design(string n){
	desname=n;
}
Design::~Design()
{
	//clear dynamic memory
	map<string, Net*>::iterator itn;
	map<string, Gate*>::iterator itg;
	for (itn=design_nets.begin();itn!=design_nets.end();itn++)
	{
		delete (itn->second);
	}
	design_nets.clear();
	for (itg=design_gates.begin();itg!=design_gates.end();itg++)
	{
		delete (itg->second);
	}
	design_gates.clear();
}

string Design::name(){
	return desname;
}
void Design::add_pi(string n){
	pis.push_back(n);
}
void Design::add_po(string n){
	pos.push_back(n);
}

Net* Design::find_net(string net_name){
	map<string, Net*>::iterator it;
	it=design_nets.find(net_name);
	if(it!=design_nets.end())
		return it->second;
	else
		return NULL;
}

Gate* Design::find_gate(string inst_name){
	map<string, Gate*>::iterator it;
	it=design_gates.find(inst_name);
	if(it!=design_gates.end())
		return it->second;
	else
		return NULL;
}

Net* Design::add_find_net(string n){
	map<string, Net*>::iterator it;
	it=design_nets.find(n);
	if(it!=design_nets.end())
		return it->second;
	else{
		Net* temp=new Net(n);
		design_nets[n]=temp;
		return temp;
	}
}
//create gates according to gatetypes
Gate* Design::add_find_gate(int gtype, string n, int delay){
	map<string, Gate*>::iterator it;
	it=design_gates.find(n);
	if(it!=design_gates.end())
		return it->second;
	else{
		if (gtype==0){
			And* temp=new And(n,delay);
			design_gates[n]=temp;
			return temp;
		}

		if (gtype==1){
			Or* temp=new Or(n,delay);
			design_gates[n]=temp;
			return temp;
		}
		if (gtype==2){
			Nand* temp=new Nand(n,delay);
			design_gates[n]=temp;
			return temp;
		}

		if (gtype==3){
			Nor* temp=new Nor(n,delay);
			design_gates[n]=temp;
			return temp;
		}

		if (gtype==4){
			Xor* temp=new Xor(n,delay);
			design_gates[n]=temp;
			return temp;
		}

		if (gtype==5){
			Not* temp=new Not(n,delay);
			design_gates[n]=temp;
			return temp;
		}
	}
}


vector<Net *> * Design::get_pi_nets(){
	vector<Net *>* temp=new vector<Net*>;
	vector<string>::iterator it;
	for(it=pis.begin();it!=pis.end();it++)
		temp->push_back(design_nets[*it]);
	return temp;
}
vector<Net *> * Design::get_po_nets(){
	vector<Net *>* temp=new vector<Net*>;
	vector<string>::iterator it;
	for(it=pos.begin();it!=pos.end();it++)
		temp->push_back(design_nets[*it]);
	return temp;
}
vector<Net *> *Design::get_wire_nets(){
	bool flag;
	vector<Net *>* temp=new vector<Net*>;
	map<string, Net *>::iterator it;
	for(it=design_nets.begin();it!=design_nets.end();it++){
		vector<string>::iterator it1,it2;
		flag=false;
		//to see if net is in pis
		for(it1=pis.begin();it1!=pis.end();it1++){
			if((*it1)==(it->first)){
				flag=true;
				break;
			}
		}
		//tp see if net is in pos
		for(it2=pos.begin();it2!=pos.end();it2++){
			if((*it2)==(it->first)){
				flag=true;
				break;
			}
		}
		// not in both, net must be a wire
		if(flag==false)
			temp->push_back(it->second);
	}

	return temp;
}

vector<Net*>* Design::all_nets()
{
	vector<Net*>* temp=new vector<Net*>;
	map<string, Net*>::iterator it;
	for (it=design_nets.begin();it!=design_nets.end();it++)
	{
		temp->push_back(it->second);
	}
	return temp;
}

vector<Gate*>* Design::all_gates()
{
	vector<Gate*>* temp=new vector<Gate*>;
	map<string, Gate*>::iterator it;
	for (it=design_gates.begin();it!=design_gates.end();it++)
	{
		temp->push_back(it->second);
	}
	return temp;
}

map<string,Net*> Design::get_net_map()
{
    return design_nets;
}
//dump the result.
void Design::dump(ostream &os)
{
	vector<string>::iterator iti;
	vector<string>::iterator ito;
	os<<"module "<<desname<<"("<<pis[0];
	for (iti=pis.begin()+1;iti!=pis.end();iti++)
	{
		os<<", "<<(*iti);
	}
	for (ito=pos.begin();ito!=pos.end();ito++)
	{
		os<<", "<<(*ito);
	}
	os<<");"<<endl;

	for (iti=pis.begin();iti!=pis.end();iti++)
	{
		os<<"input "<<(*iti)<<";"<<endl;
	}

	for (ito=pos.begin();ito!=pos.end();ito++)
	{
		os<<"output "<<(*ito)<<";"<<endl;
	}

	vector<Net*>* wires=get_wire_nets();
	vector<Net*>::iterator itw;
	for (itw=wires->begin();itw!=wires->end();itw++)
	{
		os<<"wire "<<(*itw)->name()<<";"<<endl;
	}
	map<string,Gate*>::iterator itg;
	for (itg=design_gates.begin();itg!=design_gates.end();itg++)
	{
		itg->second->dump(os);
	}
	os<<"endmodule ";
	delete wires;
}
