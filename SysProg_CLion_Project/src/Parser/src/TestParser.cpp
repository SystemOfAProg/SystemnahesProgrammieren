#include "../includes/Parser.h"
#include "../includes/ParseTree.h"
#include "../includes/ParseTreeVisitor.h"
#include "../includes/TypeChecker.h"
#include "../includes/CodeGenerator.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	if(argv[1] != NULL) {
		cout << "[Parser]: Parse code listed in " << argv[1] << endl;
		Parser* parser = new Parser(argv[1]);
		ParseTree* tree = parser->parse();
		cout << "[Parser]: Check types of code listed in " << argv[1] << endl;
		TypeChecker tc;
		tc.typeCheck(tree);
		if(argv[2] != NULL) {
			cout << "[Parser]: Write generated code into " << argv[2] << endl;
			CodeGenerator mc;
			mc.makeCode(tree, argv[2]);
		} else {
			cerr << "[Parser]: Code could not be generated, because no output file was passed to the Parser." << endl;
		}
	}

}
