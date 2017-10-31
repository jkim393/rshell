#ifndef _CMDOR_H_
#define _CMDOR_H_

	class cmdOr : public cmdConn {
		public: 
			1cmdOr(): cmdConn() {};
			cmdOr(cmdBase* left, cmdBase* right) : cmdConn(left, right) {};
			bool evaluate();


#endif
