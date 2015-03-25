/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "net.h"
#include "gates.h"

using namespace std;

Net::Net()
{
	drivers=new vector<Gate *>;
	loads=new vector<Gate *>;
	//initialize val of net to X
	val='X';
	//used for dfs searching
	sort=0;
	//used for calculating final delay
	delay=0;
}

Net::Net(string n)
{
	netname=n;
	drivers=new vector<Gate *>;
	loads=new vector<Gate *>;
	val='X';
	sort=0;
	delay=0;
}

Net::~Net()
{
	delete drivers;
	delete loads;
}

void Net::addDriver(Gate *g)
{
	drivers->push_back(g);
}

void Net::addLoad(Gate *g)
{
	loads->push_back(g);
}

vector<Gate *> * Net::getLoads()
{
	return loads;
}

vector<Gate *> * Net::getDrivers()
{
	return drivers;
}

string Net::name()
{
	return netname;
}

void Net::setVal(char v)
{
	val=v;
}
//function to compute the val of net
char Net::computeVal()
{
	//more need to be done
	vector<Gate *>::iterator itd;
	vector<char> values;
	if (drivers->empty())
	{
		return val;
	}
	for (itd=drivers->begin();itd!=drivers->end();itd++)
	{
		values.push_back((*itd)->eval());
	}
	if (values[0]=='X'){
		val='X';
		return val;
	}
	vector<char>::iterator itv;
	for (itv=values.begin()+1;itv!=values.end();itv++)
	{
		if ((*itv)=='X')
		{
			val='X';
			return val;
		}
		if ((*itv)!=values[0])
		{
			val='X';
			return val;
		}
	}

	val=values[0];
	return val;
}

char Net::getVal()
{
	return val;
}

void Net::printDriversLoads()
{
	vector<Gate *>::iterator itd;
	vector<Gate *>::iterator itl;
	if(!drivers->empty()){
	cout<<"The drivers for this net is: "<<endl;
	for (itd=drivers->begin();itd!=drivers->end();itd++)
	{
		cout<<(*itd)->name()<<" ";
	}
	cout<<endl;
	}
	if(!loads->empty()){
	cout<<"The loads for this net is: "<<endl;
	for (itl=loads->begin();itl!=loads->end();itl++)
	{
		cout<<(*itl)->name()<<" ";
	}
	cout<<endl;
	}
}
//function to compute delay
void Net::computeDelay()
{
    //priority queue used to produce largest delay for the current net
    priority_queue<int> pq;
    vector<Gate*>::iterator itg;
    vector<Net*>::iterator itn;
    vector<Net*>* gate_inputs;
    //calculate when the net has drivers
    if (!drivers->empty())
    {

    for (itg=drivers->begin();itg!=drivers->end();itg++)
    {
        gate_inputs=(*itg)->getInputs();
        for (itn=gate_inputs->begin();itn!=gate_inputs->end();itn++)
        {
            pq.push(((*itn)->delay)+((*itg)->getDelay()));//delay= delay of dirver+delay of previous net.
        }
    }
    delay=pq.top();
    }
}


