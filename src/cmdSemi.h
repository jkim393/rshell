#ifndef _CMDSEMI_H_
#define _CMDSEMI_H_
#include "cmdConn.h"

	class cmdSemi : public cmdConn {
		public:
			cmdSemi() : cmdConn() {};
			cmdSemi(cmdBase* left, cmdBase* right) : cmdConn(left, right) {};
			bool evaluate(); 			

#endif
