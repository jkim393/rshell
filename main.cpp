#include <iostream>

using namespace std;

int main()
{

bool exit = false;
string executable = "";
string argumentList = "";
string connector = "";

// I did not really add anything, just wanted a basic skeleton?
// very naive implementation
while (!exit)
	{
		cout << "$";
		cin >> executable;
		cin >> argumentList;
		cin >> connector;

		exit = true;
	}

	cout << "\n" << executable << "\n" << argumentList << "\n" << connector << endl;

return 0;
}


