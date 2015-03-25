/************pa5_part2*************/
/************Group_10**************/
/*********Zhifeng Lin, Han Xiao************/
#include <iostream>
#include <string>
#include <vector>
#include "net.h"
#include "gates.h"

Gate::Gate(){
   output=NULL;
   inputs=new vector<Net *>;

}

Gate::Gate(string n,int d){
	inst_name=n;
	delay=d;
	output=NULL;   // is it nessasary to Net()
	inputs=new vector<Net *>;
}

Gate::~Gate(){

}

string Gate::name(){
	return inst_name;
}

void Gate::addInput(Net *n){
	inputs->push_back(n);
}

void Gate::addOutput(Net *n){
	output=n;
}

vector<Net *> * Gate::getInputs(){
	return inputs;
}

Net* Gate::getOutput(){
	return output;
}

int Gate::getNumInputs(){
	return inputs->size();
}

int Gate::getDelay(){
	return delay;
}


//and implement

And::And():Gate()
{

}

And::And(string n,int d):Gate(n,d)
{

}
And::~And(){
	delete inputs;
	//later
}

char And::eval(){
	char out='1';
	vector<Net *>::iterator it;
        for(it=inputs->begin();it!=inputs->end();it++){
        	if((*it)->getVal()=='0')
		return '0';
		if((*it)->getVal()=='1'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='1';
			if(out=='0')
			out='0';
		}
		if((*it)->getVal()=='X'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='X';
			if(out=='0')
			out='0';
		}
	}
	return out;
}

void And::dump(ostream &os){
	if(delay!=0){
	os<<"and "<<"#"<<delay<<" "<<inst_name<<"("<<output->name();
	}
	else{
	os<<"and "<<inst_name<<"("<<output->name();
	}
	vector<Net *>::iterator it;
	for(it=inputs->begin();it!=inputs->end();it++)
	os<<", "<<(*it)->name();
	os<<");"<<endl;
}

//or implement

Or::Or():Gate()
{

}

Or::Or(string n,int d):Gate(n,d)
{

}
Or::~Or(){
	delete inputs;
	//later
}

char Or::eval(){
	char out='0';
	vector<Net *>::iterator it;
        for(it=inputs->begin();it!=inputs->end();it++){
        	if((*it)->getVal()=='1')
		return '1';
		if((*it)->getVal()=='0'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='1';
			if(out=='0')
			out='0';
		}
		if((*it)->getVal()=='X'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='1';
			if(out=='0')
			out='X';
		}
	}
	return out;
}

void Or::dump(ostream &os){
	if (delay!=0){
	os<<"or "<<"#"<<delay<<" "<<inst_name<<"("<<output->name();
	}
	else{
	os<<"or "<<inst_name<<"("<<output->name();
	}
	vector<Net *>::iterator it;
	for(it=inputs->begin();it!=inputs->end();it++)
	os<<", "<<(*it)->name();
	os<<");"<<endl;
}

//nand implement

Nand::Nand():Gate()
{

}

Nand::Nand(string n,int d):Gate(n,d)
{

}
Nand::~Nand(){
	delete inputs;
	//later
}

char Nand::eval(){
	char out='1';
	vector<Net *>::iterator it;
        for(it=inputs->begin();it!=inputs->end();it++){
        	if((*it)->getVal()=='0')
		return '1';
		if((*it)->getVal()=='1'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='1';
			if(out=='0')
			out='0';
		}
		if((*it)->getVal()=='X'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='X';
			if(out=='0')
			out='0';
		}
	}

	if(out=='1')
	out='0';
	else if(out=='0')
	out='1';

	return out;
}

void Nand::dump(ostream &os){
	if (delay!=0){
	os<<"nand "<<"#"<<delay<<" "<<inst_name<<"("<<output->name();
	}
	else{
	os<<"nand "<<inst_name<<"("<<output->name();
	}
	vector<Net *>::iterator it;
	for(it=inputs->begin();it!=inputs->end();it++)
	os<<", "<<(*it)->name();
	os<<");"<<endl;
}

//nor implement

Nor::Nor():Gate()
{

}

Nor::Nor(string n,int d):Gate(n,d)
{

}
Nor::~Nor(){
	delete inputs;
	//later
}

char Nor::eval(){
	char out='0';
	vector<Net *>::iterator it;
        for(it=inputs->begin();it!=inputs->end();it++){
        	if((*it)->getVal()=='1')
		return '0';
		if((*it)->getVal()=='0'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='1';
			if(out=='0')
			out='0';
		}
		if((*it)->getVal()=='X'){
			if(out=='X')
			out='X';
			if(out=='1')
			out='1';
			if(out=='0')
			out='X';
		}
	}

	if(out=='1')
	out='0';
	else if(out=='0')
	out='1';

	return out;
}

void Nor::dump(ostream &os){
	if (delay!=0){
	os<<"nor "<<"#"<<delay<<" "<<inst_name<<"("<<output->name();
	}
	else{
	os<<"nor "<<inst_name<<"("<<output->name();
	}
	vector<Net *>::iterator it;
	for(it=inputs->begin();it!=inputs->end();it++)
	os<<", "<<(*it)->name();
	os<<");"<<endl;
}

//xor implement

Xor::Xor():Gate()
{

}

Xor::Xor(string n,int d):Gate(n,d)
{

}
Xor::~Xor(){
	delete inputs;
	//later
}

char Xor::eval(){
	int one=0;
	vector<Net *>::iterator it;
        for(it=inputs->begin();it!=inputs->end();it++){
        	if((*it)->getVal()=='X')
		return 'X';

		if((*it)->getVal()=='1')
		one++;
	}
	if(one%2==0)
        return '0';
	else
	return '1';
}

void Xor::dump(ostream &os){
	if (delay!=0)
	{
	os<<"xor "<<"#"<<delay<<" "<<inst_name<<"("<<output->name();
	}
	else{
	os<<"xor "<<inst_name<<"("<<output->name();
	}
	vector<Net *>::iterator it;
	for(it=inputs->begin();it!=inputs->end();it++)
	os<<", "<<(*it)->name();
	os<<");"<<endl;
}

//not implement

Not::Not():Gate()
{

}

Not::Not(string n,int d):Gate(n,d)
{

}
Not::~Not(){
	delete inputs;
	//later
}

char Not::eval(){
	int zero=0,one=0;
	char out;
	vector<Net *>::iterator it;
        for(it=inputs->begin();it!=inputs->end();it++){
        	if((*it)->getVal()=='X')
		return 'X';
		if((*it)->getVal()=='0'){
		zero++;
		out='1';
		}
		if((*it)->getVal()=='1'){
		one++;
		out='0';
		}
	}
	if(zero*one != 0)
	return 'X';
	if(zero*one==0)
	return out;
}

void Not::dump(ostream &os){
	if (delay!=0){
	os<<"not "<<"#"<<delay<<" "<<inst_name<<"("<<output->name();
	}
	else{
	os<<"not "<<inst_name<<"("<<output->name();
	}
	vector<Net *>::iterator it;
	for(it=inputs->begin();it!=inputs->end();it++)
	os<<", "<<(*it)->name();
	os<<");"<<endl;
}

