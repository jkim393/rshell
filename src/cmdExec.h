#ifndef _CMDEXEC_H_
#define _CMDEXEC_H_

#include "cmdBase.h"

class cmdExec : public cmdBase {
	private:
		string command;
		arg[];

	public:
		cmdExec() {}
		cmdExec(string cmd);
		bool evaluate();

};
#endif
