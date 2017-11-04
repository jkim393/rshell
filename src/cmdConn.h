#ifndef _CMDCONN_H_
#define _CMDCONN_H_
#include "cmdBase.h"

class cmdConn : public cmdBase {
	protected:
		cmdBase* left;
		cmdBase* right;

	public:	
		cmdConn() : cmdBase(){}
		cmdConn(cmdBase* l, cmdBase* r): left(l), right(r){}
		virtual bool evaluate() = 0;

};

#endif
