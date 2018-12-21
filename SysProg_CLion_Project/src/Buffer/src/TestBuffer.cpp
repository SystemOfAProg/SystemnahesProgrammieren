using namespace std;

#include "Buffer.h"
#include "TestBuffer.h"
#include <iostream>

int main(int argc, char **argv) {
	TestBuffer* test = new TestBuffer();
	test->printStartSequence();
	test->testGetNextChar();
	test->testReturnCurrentChar();
	test->testBufferCursorPosition1();
	test->testBufferCursorPosition2();
	test->printEndSequence();
}

void TestBuffer::testGetNextChar() {
	cout << "[Test-Buffer]: Execute test for Buffer::getNextChar()." << endl;
	cout << "[Test-Buffer]: Compare the lines below with 'buffer-test-file.txt'" << endl;
	Buffer*  buffer;
	buffer = new Buffer("../assets/buffer-test-file.txt", 123);
	char c;
	do {
		c = buffer->getNextChar();
		if(c == '\n') {
			cout << "[END OF LINE]";
		}
		cout << c;
	} while(c != NULL);
	cout << "[Test-Buffer]: The test was executed properly." << endl;
	buffer->~Buffer();
}

void TestBuffer::testReturnCurrentChar() {
	cout << "[Test-Buffer]: Execute test for Buffer::returnCurrentChar()." << endl;
	cout << "[Test-Buffer]: Compare the lines below with 'buffer-test-file.txt'" << endl;
	Buffer*  buffer;
	buffer = new Buffer("../assets/buffer-test-file.txt", 123);
	char c;
	char returnCharacter;
	do {
		c = buffer->getNextChar();
		if(c==NULL){
			break;
		} else {
			returnCharacter = buffer->returnCurrentChar();
			c = buffer->getNextChar();
			cout << c;
		}
	} while(true);
	cout << endl << "[Test-Buffer]: The test was executed properly." << endl;
	buffer->~Buffer();
}

// 1. Forward run through file with only getNexts and no returnChar
void TestBuffer::testBufferCursorPosition1() {
	cout << "[Test-Buffer]: Execute test for Buffer::getCurrentLine() and Buffer::currentPositionInLine() Nr.1." << endl;
	Buffer*  buffer;
	buffer = new Buffer("../assets/buffer-position-test-file.txt", 123);
	char c;
	int expectedPosition = 0;
	int expectedLine = 1;
	int counter = 0;
	do {
		c = buffer->getNextChar();
		counter++;
		if(c == '\n') {
			// Set position to new line, if linebreak is detected
			expectedLine++;
			expectedPosition = 0;
		} else {
			// Increase expected position in current line
			expectedPosition++;
		}
		if(c != NULL) {
			cout << "(" << buffer->getCurrentLine() << "|" << buffer->getCurrentPositionInLine() << ")" << endl; 
		}
		if (TestBuffer::errorHappened(c,counter,expectedLine,expectedPosition,buffer->getCurrentLine(),buffer->getCurrentPositionInLine())) {
			return;
		}
	} while(c != NULL);
}

// 2. Mix between getting and returning characters
void TestBuffer::testBufferCursorPosition2() {
	cout << "[Test-Buffer]: Execute test for Buffer::getCurrentLine() and Buffer::currentPositionInLine() Nr.2." << endl;
	Buffer*  buffer;
	buffer = new Buffer("../assets/buffer-position-test-file.txt", 123);
	char c;
	int expectedPosition = 0;
	int expectedLine = 1;
	int counter = 0;
	// Go through first line in file (9 characters per line)
	do {
		c = buffer->getNextChar();
		counter++;
		if(c == '\n') {
			// Set position to new line, if linebreak is detected
			expectedLine++;
			expectedPosition = 0;
		} else {
			// Increase expected position in current line
			expectedPosition++;
		}
		if (TestBuffer::errorHappened(c,counter,expectedLine,expectedPosition,buffer->getCurrentLine(),buffer->getCurrentPositionInLine())) {
		return;
	}
	} while(counter<10);
	// Return character and jump back to last line
	buffer->returnCurrentChar();
	expectedLine--;
	expectedPosition = 9;
	cout << "Position Buffer: (" << buffer->getCurrentLine() << "|" << buffer->getCurrentPositionInLine() << ")" << endl;
	if (TestBuffer::errorHappened(c,counter,expectedLine,expectedPosition,buffer->getCurrentLine(),buffer->getCurrentPositionInLine())) {
		return;
	}
	buffer->returnCurrentChar();
	expectedPosition--;
	if (TestBuffer::errorHappened(c,counter,expectedLine,expectedPosition,buffer->getCurrentLine(),buffer->getCurrentPositionInLine())) {
		return;
	}
	cout << "[Test-Buffer]: The test was executed properly." << endl;
	buffer->~Buffer();
}

bool TestBuffer::errorHappened(char c, int counter, int expectedLine, int expectedPosition, int actualLine, int actualPosition) {
	if (c != NULL && (expectedLine != actualLine || expectedPosition != actualPosition)) {
		cout << "Positions do not match in round " << counter << ": Buffer(";
		cout << actualLine << "|" << actualPosition << ") <-> Control(";
		cout << expectedLine << "|" << expectedPosition << ")" << endl;
		return true;
	} else {
		return false;
	}
}

void TestBuffer::printStartSequence() {
	cout << "=================================================================" << endl;
	cout << "                      Starting TestBuffer 				          " << endl;
	cout << "=================================================================" << endl << endl;
}

void TestBuffer::printEndSequence() {
	cout << endl;
	cout << "=================================================================" << endl;
	cout << "                       End of TestBuffer 				          " << endl;
	cout << "=================================================================" << endl;
}
