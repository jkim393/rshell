#include <iostream>
#include <cstring>
#include <vector>

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



void removeSemis(vector< vector<char*> > &finishedVect)
	{
		int i = 0;
		int x = 0;
		char* last_lett;
		
		for (i = 0; i < finishedVect.size(); ++i)
				{
					for (x = 0; x < finishedVect.at(i).size(); ++x)
						{
							last_lett = &(finishedVect.at(i).at(x)[strlen(finishedVect.at(i).at(x))-1]);
							if (*(last_lett) == ';')
								{
									finishedVect.at(i).at(x)[strlen(finishedVect.at(i).at(x)) - 1] = 0;
								}
							}
					}				
		}

void cmdPrompt(vector< vector<char*> > &cmdVector)
{

	string userInput = "";	//test string
	cout << "$ ";	//outputs $
	getline(cin, userInput); //get inputted string
	userInput = userInput.substr(0, userInput.find("#"));
	char str[userInput.size()];	//creates character array with string size
	strcpy(str,userInput.c_str());	//turn string into character string and store in str[]
	char* pch;	//used to iterate through list
	pch = strtok(str, " ");
	char* last_letter = &(pch[strlen(pch)-1]);
	char* orsign = new char('|');		//orsign pointer pointing to or sign
	char* andsign = new char('&');		//andsign pointer pointing to and sign
	bool connectorTrue = false; // checks if previous parse was a connector 
	vector<char*> andSign;
	andSign.push_back(andsign);
	vector<char*> orSign;
	orSign.push_back(orsign);
	while (pch != NULL)
	{
		if (connectorTrue)
			{
				vector<char*> tempVect;
				tempVect.push_back(pch);
				cmdVector.push_back(tempVect);
					if (*(last_letter) == '|' || *(last_letter) == '&' || *(last_letter) == ';')
						{
							connectorTrue = true;
						}
						else
						{
							connectorTrue = false;
						}
					}
					
		else if(*(last_letter) == ';')							// HANDLES THE SEMI COLON
			{ 
				if(cmdVector.size() == 0)
					{
						vector<char*> tempVect;
						tempVect.push_back(pch);
			    	cmdVector.push_back(tempVect);
						connectorTrue = true;
					}
				else
					{
        	 cmdVector.back().push_back(pch);
        	 connectorTrue = true; // previous was a connector
					}
			}  
  	else if (*(last_letter) == '|')					//HANDLES THE ||
			{
				cmdVector.push_back(orSign);
				connectorTrue = true; //previous was a connector
			}
		else if (*(last_letter) == '&')
			{
				cmdVector.push_back(andSign);
				connectorTrue = true; //previous was a connector
			}
		else 
		{
			if(cmdVector.size() == 0)
			{
				vector<char*> tempVect;
				tempVect.push_back(pch);
				cmdVector.push_back(tempVect);
			}
			else
		  {
				cmdVector.back().push_back(pch);
			}
		}
		  pch = strtok(NULL," ");
			if (pch != NULL)
			{
			  last_letter = &(pch[strlen(pch)-1]);
			}
	}
	int a = 0;
	int b = 0;
	for (a = 0; a < cmdVector.size(); ++a)
		{
			for (b = 0; b < cmdVector.at(a).size(); ++b)
				{
					cout << cmdVector.at(a).at(b) << ' ';
				}
			cout << endl;
		}
	
	
	removeSemis(cmdVector); // this command removes the semis before returning
	return;
}


int main()
{
	vector< vector<char*> > execVect;   // this is a vector that holds the 2d array of commands + connectors (no semis)
	cmdPrompt(execVect); // this is what creates the array
	
  int a = 0;
	int b = 0;
	for (a = 0; a < execVect.size(); ++a)
			{
				for (b = 0; b < execVect.at(a).size(); ++b)
					{
						cout << execVect.at(a).at(b) << ' ';
					}
			cout << endl;
			}
	cout << execVect.size() << endl;

return 0;
}
