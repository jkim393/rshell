//this is a test file for executable
#include <iostream>
#include "cmdBase.h"
//#include "cmdConn.h"
//#include "cmdAnd.h"
//#include "cmdOr.h"
//#include "cmdSemi.h"
#include "cmdExec.h"
#include <vector>
#include <string>

using namespace std;
int main () {
	vector<char*> v;
	string ls = "ls";
	char* l = (char*)ls.c_str();
	v.push_back(l);
	cmdExec A = cmdExec(v);
	
	A.evaluate();



return 0;
}
