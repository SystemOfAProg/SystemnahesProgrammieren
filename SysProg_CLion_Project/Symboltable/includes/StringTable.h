#ifndef STRINGTABLE_H_
#define STRINGTABLE_H_

#include "../includes/StringTabNode.h"

class StringTable {
	public:
		StringTable();
		virtual ~StringTable();
		char* insert(char* lexem);
		void print();
	private:
		char* freePosition;
		unsigned int freeSpace;
		StringTabNode* firstNode;
		StringTabNode* currentNode;
		unsigned int countCharacters(char* lexem);
		bool addStringTabNodeIfNecessary(unsigned int lexemLength, char* lexem);
};

#endif /* STRINGTABLE_H_ */
