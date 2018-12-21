using namespace std;
#include <iostream>
#include "../includes/Information.h";

Information::Information(char* nameInStringTable, unsigned int key) {
    this->key = key;
    this->name = nameInStringTable;
}

Information::~Information() {
    // Delete here everything in case heap memory is allocated with keyword "new"
}

char* Information::getName() {
    return this->name;
}

bool Information::equals(char* lexem) {
    char* toCompare = this->name;
    if(toCompare == NULL || lexem == NULL) {
        cout << "Null Pointer in compareLexem() in class Infromation." << endl;
        return false;
    }
    while(*lexem != '\n' && *toCompare != '\n' && *lexem != '\0' && *toCompare != '\0') {
        if(*toCompare != *lexem) {
            cout << "Lexems are not the same. 1: " << *toCompare << ", 2: " << *lexem << endl;
            return false;
        }
        lexem++;
        toCompare++;
    }
    return true;
}

unsigned int Information::getKey() {
    return this->key;
}



