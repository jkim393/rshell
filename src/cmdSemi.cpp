#include "cmdSemi.h"
#include <cstddef>

cmdSemi::cmdSemi(cmdBase* left) {
	this->left = left;
	this->right = NULL;
}

bool cmdSemi::evaluate() {
	if (left->evaluate() ) {
		return true;
	}
}
