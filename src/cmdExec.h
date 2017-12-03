#ifndef _CMDEXEC_H_
#define _CMDEXEC_H_

#include "cmdBase.h"
#include <vector>

//Assuming that char* array is passed into the constructor
//use a vector instead and then convert it later
class cmdExec : public cmdBase {
	private:
		std::vector<char*> v;
		
	public:
		cmdExec():cmdBase() {}
		cmdExec(std::vector<char*> p); //take in the array whose first element is command
		bool checkRedirection(std::vector<char*> testingVector);
		bool evaluate(); //execute the command
		bool runTest(std::vector<char*> testVector);
		bool isExec();
};
#endif


//for execvp to work the array must end with a NULL Pointer.
//however, adding to the end of the array is difficult so should I use a vector instead???
