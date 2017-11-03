#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
/*
Basically I am going to to parse by spaces and check each token for ;,||,&&. I check the semi colon condition which automatically
puts the semi colon on a new line. If it is false, i do not create a new vector row but instead simply add a new value to the same 
iteration. if a connector is detected i create a new row and iterate. for semi colon this is a special case where i detach the semi colon
and add it to a new row and continue iterating. 
*/

void cmdPrompt()
{

	string userInput = "";	//test string
	cout << "$ ";	//outputs $
	getline(cin, userInput); //get inputted string
	char str[userInput.size()];	//creates character array with string size
	strcpy(str,userInput.c_str());	//turn string into character string and store in str[]
	char* pch;	//used to iterate through list
	pch = strtok(str, " ");
	char* last_letter = &(pch[strlen(pch)-1]);
	vector< vector<char*> > cmdVector;
	char* orsign = new char('|');		//orsign pointer pointing to or sign
	char* andsign = new char('&');		//andsign pointer pointing to and sign
	bool connectorTrue = false; // checks if previous parse was a connector 
	vector<char*> andSign;
	andSign.push_back(andSign);
	while (pch != NULL)
	{

		if (*(last_letter) == ';')							// HANDLES THE SEMI COLON
			{ 
				cmdVector.back().push_back(pch);
				connectorTrue = true; // previous was a connector
			}  
   else if (*(last_letter) == '|')					//HANDLES THE ||
			{
				cmdVector.push_back.push_back(orsign);
				connectorTrue = true; //previous was a connector
			}
		else if (*(last_letter) == '&')
			{
				cmdVector.push_back(andsign);
				connectorTrue = true; //previous was a connector
			}
		else if (connectorTrue)								//HANDLES THE &&
			{
				cmdVector.push_back.push_back(pch); 
				connectorTrue = false;
			}
		else 
		{
			cmdVector.back().push_back(pch);
		}
			last_letter = &(pch[strlen(pch)-1]);
			pch = strtok(NULL, " ");
	}
	
	//all arguments are in cmdVector, we now will add the connectors

	
	

	return;
}


int main()
{

	cmdPrompt();
	

return 0;
}


