#ifndef _CMDCONN_H_
#define _CMDCONN_H_


class cmdConnector : public cmdBase {
	protected:
		cmdBase* left;
		cmdBase* right;

	public:	
		cmdConnector() : cmdBase(){};
		cmdConnector(cmdBase* l, cmdBase* r): left (l), right(r){};
		cmdBase* get_left() {return left;};
		cmdBase* get_right() {return right;};
		virtual bool evaluate() = 0;

};

#endif
