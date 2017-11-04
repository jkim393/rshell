#include <iostream>
#include <cstring>
#include <vector>
#include "cmdExec.h"

using namespace std;
/*
Basically main calls cmdPrompt function which outputs a dollar sign. This
function does the parsing pretty much and calls removeSemis where it removes all semis
I have a test at the end to output the 2d array and 1 at end of cmdPrompt before semi colons removed
* (thats why it may seem it was printed twice) and the last number is the size of vector
pretty much after cmdPrompt is called, execVect is a successful 2d array in form
* ls -a; mkdir Nikhil || mkdir Ji_Hwan || ls -a && git branch
* 
* this equals
* 
* ls -a
* mkdir Nikhil
* |
* mkdir Ji_hwan
* |
* ls -a
* &
* git branch
* 
* and of course the arguments are stored in different char* places
*/



void removeSemis(vector<char*> &finishedVect)
{
		char* last = finishedVect.back(); //last = nikhil;\0

		last[strlen(last) - 1] = 0;
		
		return;
		
}

int main()
{
	bool checker = true;
	while(checker){
	vector< vector<char*> > cmdVector;   // this is a vector that holds the 2d vector: of commands + connectors (no semis)
	//cmdPrompt(execVect); // this is what creates the 2d vector
  
	string userInput = "";	//test string
	cout << "$ ";	//outputs $
	getline(cin, userInput); //get inputted strin
	string temp = userInput.substr(0,4);
	if (temp == "exit")
	{
		return 0;
	}
	userInput = userInput.substr(0, userInput.find("#"));
	
	char str[userInput.size()];	//creates character array with string size
	strcpy(str,userInput.c_str());	//turn string into character string and store in str[]
	char* pch;	//used to point at tokens
	pch = strtok(str, " ");
	char* last_letter = &(pch[strlen(pch)-1]);
	bool connectorTrue = false; // checks if previous parse was a connector 
	//string a = "&&";
//	string o = "||";
//	char* orsign = (char*) o.c_str();		//orsign pointer pointing to or sign
//	char* andsign = (char*) a.c_str();		//andsign pointer pointing to and sign
	char* orsign = new char('|');
	char* andsign = new char('&');
	vector<char*> andSign;
	andSign.push_back(andsign);
	vector<char*> orSign;
	orSign.push_back(orsign);
	char* semi = new char(';');		
	vector<char*> semiSign;
	semiSign.push_back(semi);
	while (pch != NULL)
	{
		 if(cmdVector.size() == 0) 		  						//cmdVector parse when vector is empty (i.e. first pch)
		 {
			 	vector<char*> tempVect;
				tempVect.push_back(pch); 								// a vector containing (ls; or just ls) is made
				cmdVector.push_back(tempVect);// a vector containing (ls; or just ls) is pushed to first row of the cmdVector
				connectorTrue = false;

				if (*(last_letter) == ';') //if it ends with ; (e.g. ls;)
				{
						removeSemis( cmdVector.back() ); //pass in the current vector of char* that just got pushed in
						cmdVector.push_back(semiSign); //a vector containing (;) is pushed to next row of the cmdVector
						connectorTrue = true;
				} 
		 }	


			else //not first pch
			{
						if(connectorTrue)//previous parse was a connector, this one must be added as a new row to cmdVector
						{
							vector<char*> tempVect;
							tempVect.push_back(pch); // a vector containing command/argument (e.g. ls) is made
							cmdVector.push_back(tempVect); //added as a new row
							connectorTrue = false;
							if (*(last_letter) == ';') //if it ends with ; (e.g. ls;)
							{
								removeSemis( cmdVector.back() ); //pass in the current vector of char* that just got pushed in
								cmdVector.push_back(semiSign); //a vector containing (;) is pushed to next row of the cmdVector
								connectorTrue = true;
							} 
						}
						else if ( *(last_letter) == '&' ) //lastletter is &
						{
							cmdVector.push_back(andSign);
							connectorTrue = true; //set previous as connector
						}
						else if ( *(last_letter) == '|' ) //lastletter is |
						{
							cmdVector.push_back(orSign);
					 	 	connectorTrue = true; //previous  as connector
						}

						else //previous was not a connector and this may be a connector or command, this one must be added to the current row
						{
							if ( *(last_letter) == ';' ) //lastletter is ;
							{
								cmdVector.back().push_back(pch);
								removeSemis( cmdVector.back() );
								cmdVector.push_back(semiSign);
								connectorTrue = true; //previous was a connector
							}
							else
							{ 
						 		cmdVector.back().push_back(pch);
							}
						}	
			}

			pch = strtok(NULL," "); //next token
			if (pch != NULL)
			{
				last_letter = &(pch[strlen(pch)-1]);
			}

	}
		
		if (cmdVector.size() != 0)
		{
			unsigned int k = 1;
			bool leftChild  = false;
			cmdExec A = cmdExec(cmdVector.at(0));
			leftChild = A.evaluate();
			while (k < cmdVector.size())
			{
				if (*(cmdVector.at(k).at(0)) == ';') // THIS WILL HANDLE IF CONNECTOR IS A SEMI COLON
				{
					cmdExec A = cmdExec(cmdVector.at(k+1));
					leftChild = A.evaluate();
					k = k + 2;
				}

				else if (*(cmdVector.at(k).at(0)) == '|')
				{
					if (leftChild == true)
					{
						k = k + 2;
					}
					else {
						cmdExec A = cmdExec(cmdVector.at(k+1));
						leftChild = A.evaluate();
						k = k + 2;
					}
				}
				
				else if (*(cmdVector.at(k).at(0)) == '&')
				{
					if (leftChild == true)
					{
						cmdExec A = cmdExec(cmdVector.at(k+1));
						leftChild = A.evaluate();
						k = k + 2;
					}
					else {
						k = k + 2;
					}
				}

				
			}
		}
		
			







}
return 0;
}
