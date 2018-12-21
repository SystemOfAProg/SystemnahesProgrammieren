/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
	public:
		Buffer(const char* fileName, int size);
		virtual ~Buffer();
		char getNextChar();
		int getCurrentLine();
		int getCurrentPositionInLine();
		char getCurrentChar();
		char returnCurrentChar();
		int fillUpBuffer(char*);
		void printDebugInfo();
		void printCurrentDirectory();
	private:
		enum PositionChange {
			nextLine,
			stepForward,
			stepBackward
		};
		char* next;
		char* buffer1;
		char* buffer2;
		int currentLine;
		int currentPositionInLine;
		int lastPositionInLastLine;
		const char* fileName;
		int size;
		int lastCharInBuffer;
		int lastReadIndex;
		void setPosition(PositionChange position);
};

#endif /* BUFFER_H_ */
