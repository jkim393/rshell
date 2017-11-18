#ifndef __CMDBASE_H__
#define __CMDBASE_H__


class cmdBase 			//Base class
{
	public:
		cmdBase* left = 0;
		cmdBase* right = 0;
		//constructors
		cmdBase(){}	
		//functions
		void set(cmdBase* l, cmdBase* r) {this->left = l; this->right = r;}
		//void setL(cmdBase* l) {this->left = l;}
		//void setR(cmdBase* r) {this->right = r;}
		virtual bool evaluate() = 0; // pure virtual function
		virtual bool isExec() = 0; //tells me if it's cmdExec return true else false
};


#endif
