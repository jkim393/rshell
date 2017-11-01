#include <iostream>

using namespace std;

int main()
{

bool exit = false;
string executable = "";
string argumentList = "";
string connector = "";


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


