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
		void returnLastNCharacters(int count);
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
		int fillUpBuffer(char*);
};

#endif /* BUFFER_H_ */
