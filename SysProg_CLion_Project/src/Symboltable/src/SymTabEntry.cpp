#include "SymTabEntry.h"
#include <cstring>

SymtabEntry::SymtabEntry(Information* info) {
	this->info = info;
	this->next = NULL;
}

SymtabEntry::~SymtabEntry() {
	// TODO: delete objects created in this class
}

SymtabEntry* SymtabEntry::getNext() {
	return this->next;
}

void SymtabEntry::setNext(SymtabEntry* next) {
	this->next = next;
}

Information* SymtabEntry::getInfo() {
	return this->info;
}
