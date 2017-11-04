#ifndef __CMDBASE_H__
#define __CMDBASE_H__


class cmdBase 			//Base class
{
	public:
		//constructors
		cmdBase(){}	
 		
		//functions
		virtual bool evaluate() = 0; // pure virtual function
};


#endif
