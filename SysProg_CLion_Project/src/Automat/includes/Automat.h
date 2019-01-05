/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

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
    unsigned int index;
};

#endif /* Automat_H_ */
