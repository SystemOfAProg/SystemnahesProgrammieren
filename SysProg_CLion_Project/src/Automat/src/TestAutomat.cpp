#include "../includes/Automat.h"
#include "../../Buffer/includes/Buffer.h"
#include <iostream>
using namespace std;

char* getEnumName(int i){
	char* s;

	switch (i) {
	case 0:
		s = "Start";
		break;
	case 1:
		s = "Identifier";
				break;
	case 2:
		s = "Integer";
				break;
	case 3:
		s = "Colon";
				break;
	case 4:
		s = "Assign";
				break;
	case 5:
		s = "Equal";
				break;
	case 6:
		s = "And";
				break;
	case 7:
		s = "LogicAnd";
				break;
	case 8:
		s = "ColonBetweenEqual";
				break;
	case 9:
		s = "ColonBetweenEqualFinal";
				break;
	case 10	:
		s = "CommentStart";
				break;
	case 11:
		s = "CommentClose";
				break;
	case 12	:
		s = "CommentFinal";
				break;
	case 13:
		s = "Sign";
				break;
	case 14:
		s = "Eof";
				break;
	case 15:
		s = "Null";
				break;
	case 16	:
		s = "Error";
				break;
		};

	return s;
	}

int main (int argc, char* argv[]){
    
	Automat* automat = new Automat();

	char s[] = "X:=3+4;\n:* eine einfache Aufgabe !! *: ?y := 7 = := X : (X - 4);\nZ := ((3 + 4 - 6);\nResultat := : X y %\0$";

	cout << "automat reading..." << endl;

	int index = 0;
	while(s[index] != '$'){
        
		automat->read(s[index], 0, 0);

		index++;
		index -= automat->getBack();

		if(automat->isStop()){
			cout << "Lexem: ";
			cout << automat->getLexem()<< endl;
            cout << getEnumName(automat->getFinalState()) << endl;
			// cout << "resetting automat..." << endl;
			automat->init();
			cout << "________________" << endl;
		}
	}

	cout << "automat finished..." << endl;
}


