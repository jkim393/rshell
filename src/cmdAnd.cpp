#include "cmdAnd.h"
//#include <iostream>
//using namespace std;
bool cmdAnd::isExec() {
return false;
}

bool cmdAnd::evaluate() {
	if(left->evaluate() ) {
		//cout << "left evaluagted" << endl;
		if(right->evaluate() ){
			return true;
		}
		else {
			return false;
		}
	}
	return false; //else return false
}
