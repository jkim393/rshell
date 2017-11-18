#include "cmdExec.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

//need to add Null to the end of the vector to use execvp
cmdExec::cmdExec(std::vector<char*> p) {
	v = p;
}

bool cmdExec::isExec() {
return true;
}

bool cmdExec::runTest(vector<char*> testVector){
	
	int chequer = strcmp(testVector.at(0), "test");
	int chequer2 = strcmp(testVector.at(0), "[");
	
	if (chequer == 0) {    //format with test typed out
		testVector.erase(testVector.begin());  	//erase "test"
	}
	else if (chequer2 == 0) {           //format with square brackets [ ] erased
		testVector.erase(testVector.begin());  		//first one is "["
		testVector.pop_back();  					//last one is "]"
	}
	
	//actual running part
	struct stat fileStat; //required for stat() system call
	int fileStatChecker = stat(testVector.back(), &fileStat);
	

	if (fileStatChecker == -1) {//doesn't exist
		cout << "(False)" << endl;
		return false;
	}	
		//file check
	if (strcmp(testVector.at(0), "-f") == 0){
			if (S_ISREG(fileStat.st_mode) != 0){
				cout << "(True)" << endl;
				return true;
			}
			else {
				cout << "(False)" << endl;
				return false;
			}
	}
	  //directory check
	if (strcmp(testVector.at(0), "-d") == 0){
			if (S_ISDIR(fileStat.st_mode) != 0){
				cout << "(True)" << endl;
				return true;
			}
			else {
				cout << "(False)" << endl;
				return false;
			}
		
	}
		//-e will return true as long as fileStatChecker is not -1	
	cout << "(True)" << endl;
	return true;

}


bool cmdExec::evaluate(){
	if (v.size() == 0) { //empty case
		return false;
	}
	else if ( strcmp(v.at(0), "test") == 0 || strcmp(v.at(0), "[") == 0 ) { //test case
		return runTest(v);
	}
	

	v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
	char **command = &v[0]; //converting vector into array
	//const	char* e = "exit"; //exit function
	pid_t pid = fork();

	if (pid == 0){ //child
	//	if (command[0] == e){
			//	exit(0);	
		//}
		
		if (execvp(command[0],command) == -1) {
			perror ("exec");
			return false;
		}
	}
	
	if (pid > 0) { //parent
		
		if ( waitpid(0, NULL, 0) == -1 ) {
			perror ("wait");
		}
	}
	return true;
}
