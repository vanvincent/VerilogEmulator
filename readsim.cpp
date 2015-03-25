/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include "readsim.h"

//a function that will read the .sim file
//it needs the filename, an empty vector of string to store the names for every input net
//and it needs an empty map to associate input net's name with a vector of values to be simulated  
//will return 1 if the fillings of the simmap and the simlist are successful; otherwise, returns 0
int readsim(char* filename, vector<string> &simlist, map<string,vector<char> > &simmap)
{
	string line;
	ifstream infile;
	infile.open(filename);
	if (infile.fail())
	{
		cout<<"fail to open!"<<endl;
		return 0;
	}
	getline(infile,line);
	stringstream ss(line);
	string name;
	while(ss>>name)
	{
		simlist.push_back(name);
		vector<char> simvalue;
		simmap[name]=simvalue;
	}

	while(!getline(infile,line).eof())
	{
		stringstream ns(line);
		for (int i=0;i<simlist.size();i++)
		{
			map<string,vector<char> >::iterator it;
			it=simmap.find(simlist[i]);
			char value;
			ns>>value;
			(it->second).push_back(value);
		}
	}
	infile.close();
	return 1;
}
