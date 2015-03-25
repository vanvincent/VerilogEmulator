/************pa5_part1*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include "parse.h"
#include <iostream>
#include <sstream>
#include <set>
#include <cstdlib>
#include <fstream>

using namespace std;
//function for detecting module
string detect_module(string text,set<string> &p_list)// pass in a port set to recored all the net in module
{
	stringstream ss(text);
	string token;
	ss>>token;
	if (!ss.good())// detect key word module
	{
		return "error";
	}
	if (token!="module")
	{
		return "error";
	}
	else
	{
		string design_name;    //detect design name
		getline(ss,design_name,'(');
		if (ss.fail())
		{
			return "error";
		}
		string port_list;
		getline(ss,port_list,')');// detect port name and put it into port set
		if (!ss.good())
		{
			return "error";
		}
		ss>>token;
		if (token!=";")
		{
			return "error";
		}
		if (ss>>token)
		{
			return "error";
		}
		port_list+=" )";
		stringstream ps(port_list);
		while (ps.good())
		{
			getline(ps,token,',');
			if(!ps.good())
			{
				stringstream es(token);
				string temp;
				es>>temp;
				es>>temp;
				if(temp==")"){
					stringstream pss(token);
					string port;
					pss>>port;
					p_list.insert(port);
					break;
				}
				else{
					p_list.clear();
					return "error";
				}
			}
			else
			{
				stringstream pss(token);
				string port;
				pss>>port;
				if (pss.fail()){
					p_list.clear();
					return "error";
				}
				p_list.insert(port);

				if (pss>>port){
					p_list.clear();
					return "error";
				}
			}

		}
		stringstream ds(design_name);
		ds>>design_name;
		if (ds.fail()){
			p_list.clear();
			return "error";
		}
		return design_name;
	}
}

//detect input
string detect_input(string line,set<string> &port_list){// pass in the port set to find if the input is in  module or not
	stringstream ss(line);
	string temp,temp2;
	ss >> temp;
	if(!ss.good()){
		return "error";
	}
	if(temp!="input")
		return "error";
	else{
		getline(ss,temp,';');
		if(!ss.good())
			return "error";
		else{
			stringstream  getname(temp);
			getname>>temp;
			getname>>temp2;
			if(getname.good())
				return "error";
			else
				if (port_list.find(temp)==port_list.end())
					return "error";
				return temp;
		}
	}
}
//detect wire
string detect_wire(string line,set<string> &wire_list){// create a new set to hold all the wires
	stringstream ss(line);
	string temp,temp2;
	ss >> temp;
	if(!ss.good()){
		return "error";
	}
	if(temp!="wire")
		return "error";
	else{
		getline(ss,temp,';');
		if(!ss.good())
			return "error";
		else{
			stringstream  getname(temp);
			getname>>temp;
			getname>>temp2;
			if(getname.good())
				return "error";
			wire_list.insert(temp);
			return temp;
		}
	}
}
//detect output
string detect_output(string line,set<string> &port_list){
	stringstream ss(line);
	string temp,temp2;
	ss >> temp;
	if(!ss.good()){
		return "error";
	}
	if(temp!="output")
		return "error";
	else{
		getline(ss,temp,';');
		if(!ss.good())
			return "error";
		else{
			stringstream  getname(temp);
			getname>>temp;
			getname>>temp2;
			if(getname.good())
				return "error";
			if (port_list.find(temp)==port_list.end())
				return "error";
			return temp;
		}
	}
}
//detect gates
string detect_gates(string text,int &delay,int &gtype,set<string> &port_list,set<string> &wire_list,vector<string> &gp_list)
{
	stringstream ss(text);
	string token;
	ss>>token;
	if (!ss.good())
		return "error";
	if (token!="and"&&token!="or"&&token!="nand"&&token!="nor"&&token!="xor"&&token!="not")
		return "error";
	else
	{
		//detect gates in different gatetypes
		if (token=="and")
			gtype=0;
		if (token=="or")
			gtype=1;
		if (token=="nand")
			gtype=2;
		if (token=="nor")
			gtype=3;
		if (token=="xor")
			gtype=4;
		if (token=="not")
			gtype=5;
		string g_name;
		getline(ss,g_name,'(');
		if (ss.fail())
			return "error";
		string g_port_list;   //inset a gate port list to recore all the nets in the gate
		getline(ss,g_port_list,')');
		if (!ss.good())
			return "error";
		ss>>token;
		if (token!=";")
		{
			return "error";
		}
		if (ss>>token)
		{
			return "error";
		}

		stringstream sss(g_name);
		sss>>token;
		if (sss.fail())
			return "error";
		if (token.substr(0,1)=="#")
		{
			string temp=token.substr(1);
			delay=atoi(temp.c_str());
			sss>>g_name;
		}
		else
		{
			delay=0;
			g_name=token;
		}
		g_port_list+=" )";
		stringstream ps(g_port_list);
		while (ps.good())
		{
			getline(ps,token,',');
			if(!ps.good())
			{
				stringstream es(token);
				string temp;
				es>>temp;
				es>>temp;
				if(temp==")"){
					stringstream pss(token);
					string port;
					pss>>port;
					if (port_list.find(port)==port_list.end()&&wire_list.find(port)==wire_list.end()){
						gp_list.clear();
						return "error";
					}
					gp_list.push_back(port);
					break;
				}
				else{
					gp_list.clear();
					return "error";
				}
			}
			else
			{
				stringstream pss(token);
				string port;
				pss>>port;
				if (pss.fail()){
					gp_list.clear();
					return "error";
				}
				if (port_list.find(port)==port_list.end()&&wire_list.find(port)==wire_list.end()){
					gp_list.clear();
					return "error";
				}

				if (pss>>port){
					gp_list.clear();
					return "error";
				}
				gp_list.push_back(port);
			}

		}
		return g_name;

	}
}
//detect the end of the module
bool detect_end(string instring){
    stringstream ss(instring);
    string temp;
    ss>>temp;
	if(temp!="endmodule")
		return false;
	else
		return true;
}
//detect a blank line
bool detect_blank(string instring){
	stringstream ss(instring);
	string temp;
	ss>>temp;
	if(ss.fail ())
		return true;
	else
		return false;
}
//detect comment
bool detect_comment(string instring){
	stringstream ss(instring);
	string temp;
	ss>>temp;
	if (temp=="//")
		return true;
	else
		return false;
}

Design* parse(char* filename)
{
	Design* module=NULL;
	set<string> portlist;
	set<string> wirelist;
	int delay,gatetype,errorline=0;//errorline to detect which line has error
	vector<string> gateportlist;
	set<string> keywords;// input a list of keywors to help ues detect correct line
	keywords.insert("module");
	keywords.insert("input");
	keywords.insert("output");
	keywords.insert("wire");
	keywords.insert("not");
	keywords.insert("and");
	keywords.insert("nand");
	keywords.insert("nor");
	keywords.insert("xor");
	keywords.insert("or");
	string templine;
	bool error=false;
	ifstream infile;
	infile.open(filename);
	if(infile.fail()){
		cout<<"Fail to open!"<<endl;
		return NULL;
	}


	while(!getline(infile,templine).eof()){
		errorline++;
		if((!detect_blank(templine))&&(!detect_comment(templine))){
			stringstream ss(templine);
			string token;
			set<string>::iterator it;
			ss>>token;
			it=keywords.find(token);
			//keyword
			if(it==keywords.end()){
				cout<<"Error in line "<<errorline<<endl;
				error=true;
				break;
			}
			//end
			if(detect_end(templine))
				break;

			//detect module
			if((*it)=="module"){
				string temp;
				temp=detect_module(templine,portlist);
				if(temp=="error"){
					cout<<"Error in line "<<errorline<<endl;
					error=true;
					break;
				}else{
					module=new Design(temp);
				}
			}
			//input
			if((*it)=="input"){
				string temp;
				temp=detect_input(templine,portlist);
				if(temp=="error"){
					cout<<"Error in line "<<errorline<<endl;
					error=true;
					break;
				}else{
					module->add_pi(temp);
					Net* net=module->add_find_net(temp);
				}
			}
			//output
			if((*it)=="output"){
				string temp;
				temp=detect_output(templine,portlist);
				if(temp=="error"){
					cout<<"Error in line "<<errorline<<endl;
					error=true;
					break;
				}else{
					module->add_po(temp);
					Net* net=module->add_find_net(temp);
				}
			}
			//wire
			if((*it)=="wire"){
				string temp;
				temp=detect_wire(templine,wirelist);
				if(temp=="error"){
					cout<<"Error in line "<<errorline<<endl;
					error=true;
					break;
				}else{
					Net* net=module->add_find_net(temp);
				}
			}
			//gate
			if((*it)=="and" ||(*it)=="or"||(*it)=="not"||(*it)=="nand"||(*it)=="xor"||(*it)=="nor"){
				string temp;
				temp=detect_gates(templine,delay,gatetype,portlist,wirelist,gateportlist);
				if(temp=="error"){
					cout<<"Error in line "<<errorline<<endl;
					error=true;
					gateportlist.clear();
					break;
				}else{
					Gate* gatetemp=module->add_find_gate(gatetype,temp,delay);
					gatetemp->addOutput(module->find_net(gateportlist[0]));
					(module->find_net(gateportlist[0]))->addDriver(gatetemp);
					for(int i=1;i<gateportlist.size();i++){
						gatetemp->addInput(module->find_net(gateportlist[i]));
						(module->find_net(gateportlist[i]))->addLoad(gatetemp);
					}

					gateportlist.clear();
				}
			}



		}

	}
        infile.close();
	if(!error)
		return module;

	else if (module!=NULL){
		delete module;
		return NULL;
	}
	else
		return NULL;

}
//top function for dfs
void topdfs(vector<Net *>* outputs,vector<Net *> &netlist){ //pass in the outputs of a design and pass out a ordered netlist.
	vector<Net *>::iterator it;
	for(it=outputs->begin();it!=outputs->end();it++){
	if ((*it)->sort==0)
        dfs(*it , netlist);
	}
}
//dfs function
void dfs(Net* u,vector<Net *>& list){
	u->sort=1;
	vector<Gate*>::iterator it1;
	vector<Net*>::iterator it2;

	if((u->getDrivers())->empty()){
		u->sort=2;
		list.push_back(u);
	}else{
        	for(it1=(u->getDrivers())->begin();it1!=(u->getDrivers())->end();it1++){
                	for(it2=((*it1)->getInputs())->begin();it2!=((*it1)->getInputs())->end();it2++){
				if((*it2)->sort==0)
                    dfs(*it2,list);
			}

		}
		u->sort=2;
		list.push_back(u);
	}
}
