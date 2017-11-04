#include "cmdSemi.h"
#include <cstddef>

cmdSemi::cmdSemi(cmdBase* left) {
	this->left = left;
	this->right = NULL;
}

bool cmdSemi::evaluate() {
	bool s=	left->evaluate();
	if (s){
		return true;
	}
	return true;
}
