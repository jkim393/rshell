#include "cmdExec.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

//need to add Null to the end of the vector to use execvp
cmdExec::cmdExec(std::vector<char*> p) {
	v = p;
	v.push_back(NULL);
}

bool cmdExec::evaluate(){
	//convert vector into array
	//char* const arg[100];
	//for (unsigned int i = 0; i < v.size(); i++){
	//	arg[i] = v[i];
	//} this didn't work

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
