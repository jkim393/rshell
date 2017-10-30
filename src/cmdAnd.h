#ifndef _CMDAND_H_
#define _CMDAND_H_

	class cmdAnd : public cmdConn {
				public:
							cmdAnd(): cmdConn() {};
							cmdAnd(cmdBase* left, cmdBase* right) : cmdConn(left, right) {};
							bool evaluate();
					};



#endif
