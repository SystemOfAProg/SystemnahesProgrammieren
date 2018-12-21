#include "../includes/Symboltable.h"
#include <iostream>

const char* symTabLexems[] = {
		"position",
		"initial",
		"i",
		"thisIsAVeryLongLexem", // 20 characters
		"123456",
		"A1B2C3",
		// 1024 characters ( -> to long for stringtabnodes), exclude this from regular tests
		"0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123"
	};

int numDigits(int number) {
    int digits = 0;
    if (number < 0) digits = 1;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

// Check generated hashvalues
bool testSymTableInsert() {
	bool testSuccess = true;
	Symboltable* symboltable = new Symboltable();
	for(int i=0; i<6; i++) {
		int hashValue = symboltable->hash((char*)symTabLexems[i]);
		if (hashValue < (unsigned int)0 || hashValue > symboltable->getTableSize()) {
			std::cout << "Hash Value was not inside the Tablesizes boundary: \"" << symTabLexems[i] << "\" : " << hashValue << std::endl;
			testSuccess = false;
		}
	}
	return testSuccess;
}

bool testStringTable() {
	bool testSuccess = true;
	StringTable* st = new StringTable();
	for(int i=0; i<7; i++) {
		char* position = NULL;
		if(i == 6) {
			std::cout << "[Test-Info]: Expect not beeing able to add lexem because it is too long! If warning appears, it is correct." << std::endl;
		}
		position = st->insert((char*)symTabLexems[i]);
		if (i != 6 && position == NULL) {
			testSuccess = false;
		}
	}
	// st->print();
	st->~StringTable();
	return testSuccess;
}

// Insert all entries into the SymbolTable
bool testLookup() {
	Symboltable* st = new Symboltable();
	for (int i = 0; i<6; i++) {
		if (st->lookup((char*)symTabLexems[i]) != NULL) {
			return false;
		}
		st->insert((char*)symTabLexems[i]);
		if (st->lookup((char*)symTabLexems[i]) == NULL) {
			return false;
		}
		if (st->insert((char*)symTabLexems[i]) != st->lookup((char*)symTabLexems[i])) {
			return false;
		}
	}
	std::cout << "[Test-Info]: Expect not beeing able to add lexem because it is too long! If warning appears, it is correct." << std::endl;
	st->insert((char*)symTabLexems[6]);
	if (st->lookup((char*)symTabLexems[6]) != NULL) {
		return false;
	}
	std::cout << "[SymboltableTest]: Entries of this Symboltable:" << std::endl;
	st->dump();
	return true;
}

int main(int argc, char **argv) {
	int failedTestCounter = 0;
	if (!testSymTableInsert()) {
		std::cout << "Error in test \"testSymTableInsert()\"" << std::endl;
		failedTestCounter++;
	}
	if (!testStringTable()) {
		std::cout << "Error in test \"testStringTable()\"" << std::endl;
		failedTestCounter++;
	}
	if (!testLookup()) {
		std::cout << "Error in test \"testLookup()\"" << std::endl;
		failedTestCounter++;
	}
	std::cout << failedTestCounter << " errors happened in the test execution" << std::endl;
	return 0;
}