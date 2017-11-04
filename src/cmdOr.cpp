#include "cmdOr.h"

bool cmdOr::evaluate(){
	if(left->evaluate() ){
		return true;
	}
	else {
		if ( right->evaluate() ){
			return true;
		}
		else {
			return false;
		}
	}
}
