/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: sofa1011
 */

using namespace std;

#include "../includes/Buffer.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

Buffer::Buffer (const char* fileName, int bufferSize) {
	size = bufferSize;
	buffer1 = new char[bufferSize];
	buffer2 = new char[bufferSize];
	next = buffer1;
	this->fileName = fileName;
	lastReadIndex = 0;
	this->currentLine = 1;
	this->currentPositionInLine = 0;
	this->lastPositionInLastLine = 0;
	fillUpBuffer(buffer1);
}

Buffer::~Buffer() { }

// ================== Public Functions of Buffer ==================

char Buffer::getCurrentChar() {
	return *next;
}

char Buffer::getNextChar(){
	char c;
	c= *next;
	if (*next == NULL) {
		if (next == &buffer1[(size-1)]) {
			fillUpBuffer(buffer2);
			next = buffer2;
			return getNextChar();
		} else if (next == &buffer2[(size-1)]) {
			fillUpBuffer(buffer1);
			next = buffer1;
			return getNextChar();
		}
	} else {
		if(*next == '\n') {
			this->setPosition(PositionChange::nextLine);
		} else {
			this->setPosition(PositionChange::stepForward);
		}
		next ++;
	}
	return c;
}

char Buffer::returnCurrentChar(){
	char c;
	if (next == &buffer1[0]) {
		cout << "[Buffer]: Set pointer 'next' back to end of buffer2." << endl;
		next = &buffer2[(size-1)];
	} else if (next == &buffer2[0]) {
		cout << "[Buffer]: Set pointer 'next' back to end of buffer1." << endl;
		next = &buffer2[(size-1)];
	} else {
		next--;
	}
	c = *next;
	this->setPosition(PositionChange::stepBackward);
	return c;
}

// ================== Utilities for Buffer Reading ==================

int Buffer::fillUpBuffer(char* bufferIndex) {
	ifstream is (this->fileName, ios::binary | ios::ate);
	if (is) {
		int length = is.tellg();
		int distanceToRead;
		if((size-1) > (length - lastReadIndex)) {
			distanceToRead = (length - lastReadIndex);
		} else {
			distanceToRead = (size-1);
		}
		is.seekg (lastReadIndex, is.beg);
		is.read (bufferIndex, distanceToRead);
		bufferIndex[distanceToRead] = NULL;
		is.close();
		lastReadIndex += distanceToRead;
	}
	return 0;
}

// ================== Source Code Positioning Information ==================

int Buffer::getCurrentLine() {
	return this->currentLine;
}

int Buffer::getCurrentPositionInLine() {
	return this->currentPositionInLine;
}

void Buffer::setPosition(PositionChange position) {
	if(position == PositionChange::nextLine) {
		this->currentLine++;
		this->lastPositionInLastLine = this->currentPositionInLine;
		this->currentPositionInLine = 0;
		return;
	} else if (position == PositionChange::stepForward) {
		this->currentPositionInLine++;
	} else if (position == PositionChange::stepBackward) {
		if(this->currentPositionInLine == 0 && this->currentLine > 1) {
			this->currentPositionInLine = this->lastPositionInLastLine;
			this->lastPositionInLastLine = 0;
			this->currentLine--;
		} else if (this->currentPositionInLine > 0 && this->currentLine >= 1) {
			this->currentPositionInLine--;
		} else {
			cout << "[Buffer]: Step backward could not be applied. Maybe the cursor is already at the beginning of the file" << endl;
		}
	}
	//cout << "Current Position: (L " << this->currentLine << " | C " << this->currentPositionInLine << " )" << endl;
}

// ================== Debug Utilities ==================

void Buffer::printDebugInfo() {
	cout << "[BUFFER-DEBUG-INFO]: The size of the buffer has been set to " << size << endl;
	cout << "[BUFFER-DEBUG-INFO]: Start-Address for buffer 1:	" << ((void *) buffer1)   << endl;
	cout << "[BUFFER-DEBUG-INFO]: Start-Address for buffer 2:	" << ((void *) buffer2)   << endl;
	cout << "[BUFFER-DEBUG-INFO]: Start-Address for next:		" << ((void *) next	  )	  << endl;
}

/**
 * For debug purposes.
 */
void Buffer::printCurrentDirectory() {
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	cout << endl;
	printf("[BUFFER-DEBUG-INFO]: Current working directory is: %s\n", cwd);
}

