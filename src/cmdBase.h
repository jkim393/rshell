#ifndef __CMDBASE_H__
#define __CMDBASE_H__


class cmdBase 			//Base class
{
	protected:
		cmdBase* left = 0;
		cmdBase* right = 0;
	public:
		//constructors
		cmdBase(){}	
 		
		//functions
		void set(cmdBase* l, cmdBase* r) {this->left = l; this->right = r;}
		virtual bool evaluate() = 0; // pure virtual function
		virtual bool isExec() = 0; //tells me if it's cmdExec return true else false
};


#endif
