#include <iostream>
#include <cstring>
#include <vector>
#include "cmdExec.h"
#include "cmdBase.h"
#include "cmdConn.h"
#include "cmdAnd.h"
#include "cmdOr.h"
#include "cmdSemi.h"
#include <stack>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
using namespace std;

void destroy(cmdBase *curr){
    if(curr) {
    destroy(curr->left);
    destroy(curr->right);
    delete curr;
		}
}

void removeSemis(vector<char*> &finishedVect)
{
		char* last = finishedVect.back(); //last = nikhil;\0

		last[strlen(last) - 1] = 0;
		
		return;
		
}

void removeParenthLeft(vector<char*> &moddedVect)
{
	char* first = moddedVect.back();
	
	memmove(first, first+1, strlen(first));
	
	return;

}

void removeParenthRight(vector<char*> &moddedVect)
{
	char* last = moddedVect.back();
	
	last[strlen(last) - 1] = 0;
	
	return;
	
}
//function to createTree based on shuntingyard
cmdBase* createTree(vector<vector<char*> > v){
	//PART 1: Shuntingyard: create a postfix notation of the user's input
	//1. create an output queue and a connector stack and push everything to the output queue using shunting yard algorithm
	//queue: empty, front, back, push, pop, size
	//stack: empty, top, push, pop, size
  const char* cmd;	
	queue<vector<char*> > q;
	stack<vector<char*> > conStack; //connector stack	
	for( unsigned int i = 0; i < v.size(); i++) /*until last element of vector*/ {
			cmd = (const char *)(v.at(i).at(0));
			if (*cmd != '&' && *cmd != '|' && *cmd != ';' && *cmd != '(' && *cmd != ')' ){
				q.push(v.at(i) ); //if it's not a connector and not a parenthis it must be an executable so push that to the q
			}
			else if (*cmd == '&' || *cmd == '|' || *cmd == ';' ){ // if it's one of the connectors
				if (conStack.empty() ){
					conStack.push(v.at(i) );
					continue;
				}
				else if (*(conStack.top().at(0)) != '('  ) {
					q.push(conStack.top());
					conStack.pop();
				}
				conStack.push(v.at(i));
			}
			else if (*cmd == '(' ){
				conStack.push(v.at(i));
			}
			else if (*cmd == ')' ){
					while (*(conStack.top().at(0)) != '(' ) {
								q.push(conStack.top());
								conStack.pop();
					}
					conStack.pop();
			}
	}
	while (!conStack.empty() ) {
				q.push(conStack.top());
				conStack.pop();
	}
//q is now ready

	//PART 2: Conversion to cmdBase* and building tree
	//1. create a stack <cmdBase*>, 
	//2. loop thru q : within each iteration do the following
	//   - create cmdBase* based on its class (cmdExec or cmdAnd/cmdOr/cmdSemi) 
	//     NOTE: use strcmp which returns 0 when same
	//   - build tree by pushing to the <cmdBase*> stack
	stack<cmdBase*> myStack;while (!myStack.empty()) {
			myStack.pop();
		}
	cmdBase* A;
	while (!q.empty()) {
		cmd = (const char*)(q.front().at(0));
		if ( *cmd == '&' ) { A = new cmdAnd(); }
		else if ( *cmd == '|' ) { A = new cmdOr(); }
		else if ( *cmd == ';' ) { A = new cmdSemi(); }
		else { A = new cmdExec(q.front() ); }
		
		if (A->isExec()) {
				myStack.push(A);
		}
		else {
			cmdBase* right = myStack.top();
			//A->setR(myStack.top());
			myStack.pop();
			//A->setL(myStack.top());
			cmdBase* left = myStack.top();
			myStack.pop();
			A->set(left, right);
			myStack.push(A);
		}
			
		q.pop();
	}

//clearance
	cmdBase* root = myStack.top();
	while (!myStack.empty()) {
			myStack.pop();
	}
	return root;
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
		//if (userInput.find("exit") != std::string::npos || userInput.find("exit;") != std::string::npos) {
  	//  return 0;
		//}

		userInput = userInput.substr(0, userInput.find("#"));

		int leftCount = 0;
		int rightCount = 0;
		for (int i = 0; i < userInput.size(); ++i)
		{
			if (userInput.at(i) == '(')
			{
				leftCount = leftCount + 1;
			}
			else if (userInput.at(i) == ')')
			{
				rightCount = rightCount + 1;
			}
		}

		if (leftCount != rightCount)
		{
			cout << "Error: Missing or extra parenthesis" << endl;
			continue;
		}
	
	
	
		char str[userInput.size()];	//creates character array with string size
		strcpy(str,userInput.c_str());	//turn string into character string and store in str[]
		char* pch;	//used to point at tokens
		pch = strtok(str, " ");
		char* last_letter = &(pch[strlen(pch)-1]); // points at las character
		char* first_letter = pch;
		bool connectorTrue = false; // checks if previous parse was a connector 
		char* orsign = new char('|');
		char* andsign = new char('&');
		char* parsignLeft = new char('(');
		char* parsignRight = new char(')');
		char* semi = new char(';');	
		vector<char*> andSign;
		andSign.push_back(andsign);
		vector<char*> orSign;
		orSign.push_back(orsign);	
		vector<char*> semiSign;
		semiSign.push_back(semi);
		vector<char*> parSignLeft;
		parSignLeft.push_back(parsignLeft);
		vector<char*> parSignRight;
		parSignRight.push_back(parsignRight);
		while (pch != NULL)
		{
		 	if(cmdVector.size() == 0) 		  						//cmdVector parse when vector is empty (i.e. first pch)
		 	{
				vector<char*> tempVect;
				tempVect.push_back(pch); 								// a vector containing (ls; or just ls) is made
				cmdVector.push_back(tempVect);// a vector containing (ls; or just ls) is pushed to first row of the cmdVector
				connectorTrue = false;

				while (*(first_letter) == '(') // if it starts with a (
				{
						cmdVector.insert(cmdVector.begin(), parSignLeft); //a vector containing (() is pushed to first row of the cmdVector
						removeParenthLeft( cmdVector.back() ); // pass in the current vector of char* that just got pushed in
						connectorTrue = false;
						first_letter = cmdVector.back().at(0);
				}
			 	

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
							
							if (*(first_letter) == '(') // if it starts with a (
							{
								while (*(first_letter) == '(')
								{
									cmdVector.insert(cmdVector.begin() + (cmdVector.size() - 1), parSignLeft); //a vector containing (() is pushed to first row of the cmdVector
									removeParenthLeft( cmdVector.back() ); // pass in the current vector of char* that just got pushed in
									connectorTrue = false;
									first_letter = cmdVector.back().back();
								}
							}
						
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
							
							else if ( *(last_letter) == ')' ) // lastletter is )
							{
								int rightPar = cmdVector.size() - 1;
								cmdVector.back().push_back(pch);
								while ( *(last_letter) == ')' ) // lastletter is )
								{
									//cout << "it enters here atleast" << endl;
									//cout << pch << endl;
									removeParenthRight( cmdVector.at(rightPar) );
									cmdVector.push_back(parSignRight);
									connectorTrue = false;
									
									char* temp_letter = cmdVector.at(rightPar).back();
									last_letter = &(temp_letter[strlen(temp_letter)-1]);
								}
							}
				
							else
							{ 
						 		cmdVector.back().push_back(pch);
							}
						}	
			}//end of else

			pch = strtok(NULL," "); //next token
			if (pch != NULL)
			{
				last_letter = &(pch[strlen(pch)-1]);
				first_letter = pch;
			}

		}//end of while pch!=Null parsing ends here


		// THIS FOR LOOP ALLOWS COMMANDS SUCH AS (( echo A && echo B )) would occur 
		for (int i = 0; i < cmdVector.size(); ++i)
		{
			if (*(cmdVector.at(i).front()) == NULL)
			{
				cmdVector.at(i).erase(cmdVector.at(i).begin());
			}
		}

		//TEST CASE FOR VECTOR TO MAKE SURE ITCONTAINS EVERYTHING PARSED COORECTLY
		//  for (int i = 0; i < cmdVector.size(); i++){
		//		for (unsigned int j = 0; j < cmdVector.at(i).size(); j++){
		//			cout << cmdVector.at(i).at(j) << " ";
		//		}
		//		cout << endl;
		//	}
		//	cout << endl;

		//call function here to create the tree
		cmdBase* rooot = createTree(cmdVector);
		rooot->evaluate();
		destroy(rooot);
	} //end of the while checker

return 0;
}

