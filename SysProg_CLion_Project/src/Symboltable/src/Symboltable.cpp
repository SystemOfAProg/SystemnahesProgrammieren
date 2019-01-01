/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */


#include <iostream>
#include <iomanip>
#include "Symboltable.h"
#include "StringTable.h"
#include "StringTabNode.h"

Symboltable::Symboltable() {
	this->stringTable = new StringTable();
}

Symboltable::~Symboltable() {
	delete this->stringTable;
}

SymtabEntry* Symboltable::insert(char* lexem) {
	SymtabEntry* potentialEntry = this->lookup(lexem);
	if (potentialEntry == NULL) {
		unsigned int hash = this->hash(lexem);
		char* positionInStringTable = this->stringTable->insert(lexem);
		if (positionInStringTable != NULL) {
			Information* information = new Information(positionInStringTable, hash);
			SymtabEntry* entry = new SymtabEntry(information);
			this->addEntryToTable(entry);
			return entry;
		} else {
			return NULL;
		}
	} else {
		return potentialEntry;
	}
}

void Symboltable::addEntryToTable(SymtabEntry* entry) {
	// Check, if SymtabEntry already exisits for this hashvalue
	SymtabEntry* potentialEntry = this->table[entry->getInfo()->getKey()];
	if(potentialEntry == NULL) {
		this->table[entry->getInfo()->getKey()] = entry;
	} else {
		SymtabEntry* lastNode = potentialEntry;
		while (lastNode->getNext() != NULL) {
			lastNode = lastNode->getNext();
		}
		lastNode->setNext(entry);
	}
	return;
}

SymtabEntry* Symboltable::lookup(char* lexem) {
	unsigned int hash = this->hash(lexem);
	SymtabEntry* currentNode = this->table[hash];
	while (currentNode!= NULL) {
		if (currentNode->getInfo()->equals(lexem)) {
			return currentNode;
		}
		currentNode = currentNode->getNext();
	}
	return NULL;
}

// Write all entries of symboltable to output
void Symboltable::dump() {
	std::cout << "+--------+------------------------------------------+" << std::endl;
	std::cout << "| " << std::setw(6) << "Hash" << " | " << std::setw(40) << "Lexem" << " |" << std::endl;
	std::cout << "+--------+------------------------------------------+" << std::endl;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if(this->table[i] != NULL) {
			SymtabEntry* entry = table[i];
			do {
				Information* information = entry->getInfo();
				std::cout << "| " << std::setw(6) << information->getKey() << " | " << std::setw(40) << information->getName() << " |" << std::endl;
				entry = entry->getNext();
			} while (entry != NULL);
		}
	}
	std::cout << "+--------+------------------------------------------+" << std::endl;
}

// ==== Utilities for inserting ===

unsigned int Symboltable::hash(char* s) {
	int seed = 131; 
   	unsigned long hash = 0;
	for(int i = 0; i < this->stringLength(s); i++) {
		hash = (hash * seed) + s[i];
	}
	return hash % this->TABLE_SIZE;
}

int Symboltable::stringLength(char* lexem) {
	char* current = lexem;
	int stringLength = 0;
	while ( *current != '\0' ) {
		stringLength++;
		current++;
	}
	return stringLength;
}

unsigned int Symboltable::getTableSize() {
	return this->TABLE_SIZE;
}

void Symboltable::initSymbols() {
	
}
