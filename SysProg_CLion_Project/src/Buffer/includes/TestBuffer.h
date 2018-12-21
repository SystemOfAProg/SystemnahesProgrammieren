#ifndef TESTBUFFER_H_
#define TESTBUFFER_H_

class TestBuffer {
	public:
		void testGetNextChar();
		void testReturnCurrentChar();
		void testBufferCursorPosition1();
        void testBufferCursorPosition2();
		void printStartSequence();
		void printEndSequence();
        bool errorHappened(char c, int counter, int expectedLine, int expectedPosition, int actualLine, int actualPosition);
};

#endif /* TESTBUFFER_H_ */