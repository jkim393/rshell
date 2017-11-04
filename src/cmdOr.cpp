#include "cmdOr.h"

bool cmdOr::evaluate(){
	if(left->evaluate() || right->evaluate() ){
		return true;
	}
}
