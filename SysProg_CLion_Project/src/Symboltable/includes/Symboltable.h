#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "SymTabEntry.h"
#include "StringTable.h"

class Symboltable {
	public:
		Symboltable();
		virtual ~Symboltable();
		SymtabEntry* insert(char* lexem);
		unsigned int hash(char* s);
		unsigned int getTableSize();
		SymtabEntry* lookup(char* lexem);
		void dump();

	private:
		static const unsigned int TABLE_SIZE = 1024;
		StringTable* stringTable;
		SymtabEntry* table[TABLE_SIZE];
		int stringLength(char* lexem);
		void addEntryToTable(SymtabEntry* entry);
};

#endif /* SYMBOLTABLE_H_ */
