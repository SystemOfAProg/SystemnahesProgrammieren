#ifndef SYMTABENTRY_H_
#define SYMTABENTRY_H_

#include "Information.h"

class SymtabEntry {
	public:
		SymtabEntry(Information* info);
		virtual ~SymtabEntry();
		SymtabEntry* getNext();
		void setNext(SymtabEntry* next);
		Information* getInfo();

	private:
		SymtabEntry* next;
		Information* info;
};



#endif /* SYMTABENTRY_H_ */
