#include "cmdSemi.h"
#include <cstddef>

cmdSemi::cmdSemi(cmdBase* left) {
	this->left = left;
	this->right = NULL;
}

bool cmdSemi::evaluate() {
	bool s; //dummy bool
	s = left->evaluate();
	return true;
}
