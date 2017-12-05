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
#include <fcntl.h>

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

bool cmdExec::checkRedirection(vector<char*> testingVector){
	char* testV;
	vector<char*> testVect = testingVector;
	bool trueRedirect = false;

	for (int i = 0; i < testVect.size(); ++i)
	{
		testV = strchr(testVect.at(i), '|');
		if (testV != NULL)
		{
			string str(*(testVect.begin()),*(testVect.begin() + i));
			string str2(*(testVect.begin() + i + 1), *(testVect.end() - 1));
			str2.append(testVect.back());
			const char * a = str.c_str();
			const char * b = str2.c_str();

		FILE *pipein_fp, *pipeout_fp;
        char readbuf[1000];

        // Create one way pipe line with call to popen() 
        if (( pipein_fp = popen(a, "r")) == NULL)
        {
                perror("popen");
                return false;
        }

        // Create one way pipe line with call to popen() 
        if (( pipeout_fp = popen(b, "w")) == NULL)
        {
                perror("popen");
                return false;
        }

        //Processing loop 
        while(fgets(readbuf, 1000, pipein_fp))
                fputs(readbuf, pipeout_fp);

        //Close the pipes 
        pclose(pipein_fp);
        pclose(pipeout_fp);

        return true;


			
		}
	}
	
	for (int i = 0; i < testVect.size(); ++i)
	{
		testV = strchr(testVect.at(i), '<');
		if (testV != NULL)
		{
			trueRedirect = true;
			return trueRedirect;
		}
											
		testV = strchr(testVect.at(i), '>');
		if (testV != NULL)
		{
			trueRedirect = true;
			return trueRedirect;
		}
											
		testV = strchr(testVect.at(i), '|');
		if (testV != NULL)
		{
			trueRedirect = true;
			return trueRedirect;
		}
	
	}		
		return trueRedirect; //returns false	
}

bool cmdExec::evaluate(){
	if (v.size() == 0) { //empty case
		return false;
	}
	else if ( strcmp(v.at(0), "test") == 0 || strcmp(v.at(0), "[") == 0 ) { //test case
		return runTest(v);
	}
	else if (strcmp(v.at(0), "exit") == 0  ) { //test case without []
		_exit(0);
	}
	
	pid_t pid = fork();
	if (pid == 0){ //child
		
		// if (call function that checks if there is >,<,>>, | returns true)
  	// 		then call function that takes the thing and 
 		if (checkRedirection(v)) { 
			//case of   <  >	
			if (v.size() >= 5 && strcmp(v.at( v.size() - 2 ), ">") == 0 && strcmp(v.at( v.size() - 4 ), "<") == 0 )  {  
				const char* pathname = (const char *)v.at(v.size() - 1); //get the path name
				const char* pathname2= (const char *)v.at(v.size() - 3);
				int out = open(pathname, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				int in  = open(pathname2, O_RDONLY);
					v.pop_back();
					v.pop_back();
					v.pop_back();
					v.pop_back();
				v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
				char **command = &v[0]; //converting vector into array
				//const	char* e = "exit"; //exit function
				dup2(in, 0);
				dup2(out,1);
				close(in);
				close(out);

				if (execvp(command[0],command) == -1) {
					perror ("exec");
					return false;        //return before close might cause error
				}

			}
			//case of  >
			else if (strcmp(v.at( v.size() - 2 ), ">") == 0 ) {  
				const char* pathname = (const char *)v.at(v.size() - 1); //get the path name
				int out = open(pathname, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				
					v.pop_back();
					v.pop_back();
				
				v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
				char **command = &v[0]; //converting vector into array
				//const	char* e = "exit"; //exit function
				dup2(out,1);
				close(out);

				if (execvp(command[0],command) == -1) {
					perror ("exec");
					return false;        //return before close might cause error
				}
			}
			//case of  <
			else if (strcmp(v.at( v.size() - 2 ), "<") == 0 ) {  
				const char* pathname = (const char *)v.at(v.size() - 1); //get the path name
				int in = open(pathname, O_RDONLY);
				
					v.pop_back();
					v.pop_back();
				
				v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
				char **command = &v[0]; //converting vector into array
				//const	char* e = "exit"; //exit function
				dup2(in,0);
				close(in);

				if (execvp(command[0],command) == -1) {
					perror ("exec");
					return false;        //return before close might cause error
				}
			}
			else if (v.size() >= 5 && strcmp(v.at( v.size() - 2 ), ">>") == 0 && strcmp(v.at( v.size() - 4 ), "<") == 0 )  {  
				const char* pathname = (const char *)v.at(v.size() - 1); //get the path name
				const char* pathname2= (const char *)v.at(v.size() - 3);
				int out = open(pathname, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				int in  = open(pathname2, O_RDONLY);
					v.pop_back();
					v.pop_back();
					v.pop_back();
					v.pop_back();
				v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
				char **command = &v[0]; //converting vector into array
				//const	char* e = "exit"; //exit function
				dup2(in, 0);
				dup2(out,1);
				close(in);
				close(out);

				if (execvp(command[0],command) == -1) {
					perror ("exec");
					return false;        //return before close might cause error
				}

			}
			//case of  >>
 			else if (strcmp(v.at( v.size() - 2 ), ">>") == 0 ) {  
				const char* pathname = (const char *)v.at(v.size() - 1); //get the path name
				int out = open(pathname, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				
					v.pop_back();
					v.pop_back();
				
				v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
				char **command = &v[0]; //converting vector into array
				//const	char* e = "exit"; //exit function
				dup2(out,1);
				close(out);

				if (execvp(command[0],command) == -1) {
					perror ("exec");
					return false;        //return before close might cause error
				}
			}

			//case of |
			return true;
		}
		//another case
		else {
			v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
			char **command = &v[0]; //converting vector into array
			if (execvp(command[0],command) == -1) {
				perror ("exec");
				return false;
			}
		}
	
	}//end of child process

	if (pid > 0) { //parent
			if ( waitpid(0, NULL, 0) == -1 ) {
				perror ("wait");
			}
	}

	return true;
}
	/*
	v.push_back(NULL); 			//adding Null for the execvp needs the Null at the end
	char **command = &v[0]; //converting vector into array
	//const	char* e = "exit"; //exit function
	pid_t pid = fork();

	if (pid == 0){ //child
		
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
}*/
