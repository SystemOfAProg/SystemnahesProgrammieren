/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#define DEFAULT_ARRAY_SIZE          20000
#define NEW_SIZE                    20100

class Automat {
public:
	enum State {
			Start,
			Identifier,
			Integer,
			Error,
			Colon,
			Assign,
			Equal,
			And,
			DoubleAnd,
			ColonBetweenEqual,
			ColonBetweenEqualFinal,
			CommentStart,
			CommentClose,
			CommentFinal,
			Sign,
			Eof,
			Null
		};
	Automat();
	virtual ~Automat();
	void read(char c, unsigned int line, unsigned int column);
	State getCurrentState();
	State getLastFinalState();
	int getBack();
	char* getLexem();
	unsigned int getLine();
	unsigned int getColumn();
	bool isStop();
	void reset();
	void clearLexem();
private:
	State currentState;
	State lastFinalState;
	int back;
	bool stop;
	char* lexem;
	unsigned int sizeLexem;
	unsigned int indexLexem;
	unsigned int line;
	unsigned int column;
	bool isSign(char c);
	bool isDigit(char c);
	bool isAlpha(char c);
	void addCharToLexem(char c);
};

#endif /* Automat_H_ */
