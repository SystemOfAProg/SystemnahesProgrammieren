#ifndef Automat_H_
#define Automat_H_

#include "../../Buffer/includes/Buffer.h"

class Automat {
public:
	Automat();
	virtual ~Automat();
	enum State {
		Start,
		Identifier,
		Integer,
		Colon,
		Assign,
		Equal,
		And,
		DoubleAnd,
		LogicAnd,
		ColonBetweenEqual,
		ColonBetweenEqualFinal,
		CommentStart,
		CommentClose,
		CommentFinal,
		Sign,
		Eof,
		Null,
		Error
	};
	void init();
	State getCurrentState();
	State getFinalState();
	char* getLexem();
	int getBack();
	bool isStop();
	bool isAlpha(char c);
	bool isDigit(char c);
	bool isSign(char c);
	bool isTerminatingOrBreak(char c);
	bool addToLexem(char c);
	void checkStartState(char c);
	void read(char c);
private:
	State currentState;
	State finalState;
	bool stop;
	int stepsBack;
	char* lexem;
	static const unsigned int LEXEM_SIZE = 2048;
	void resetLexem();
	unsigned int index;
};

#endif /* Automat_H_ */
