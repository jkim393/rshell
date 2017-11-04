#ifndef _CMDEXEC_H_
#define _CMDEXEC_H_

#include "cmdBase.h"
#include <vector>

//Assuming that char* array is passed into the constructor
//use a vector instead and then convert it later
class cmdExec : public cmdBase {
	private:
		//const char* command; //pointer to constant character: command
		//char* const argv;
		std::vector<char*> v;
		
	public:
		cmdExec():cmdBase() {}
		cmdExec(std::vector<char*> p); //take in the array whose first element is command
		bool evaluate(); //execute the command

};
#endif


//for execvp to work the array must end with a NULL Pointer.
//however, adding to the end of the array is difficult so should I use a vector instead???