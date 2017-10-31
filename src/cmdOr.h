#ifndef _CMDOR_H_
#define _CMDOR_H_
#include "cmdConn.h"

	class cmdOr : public cmdConn {
		public: 
			cmdOr(): cmdConn() {};
			cmdOr(cmdBase* left, cmdBase* right) : cmdConn(left, right) {};
			bool evaluate();


#endif
