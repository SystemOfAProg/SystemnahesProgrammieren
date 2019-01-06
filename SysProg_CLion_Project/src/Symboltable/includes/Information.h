#ifndef INFORMATION_H_
#define INFORMATION_H_

#include "../../Parser/includes/Node.h"


class Information {
	public:
		Information(char* nameInStringTable, unsigned int key);
		virtual ~Information();
		char* getName();
		void setType(Node::NodeType);
		Node::NodeType getType();
		bool equals(char* lexem);
		unsigned int getKey();

	private:
		char* name;
		Node::NodeType nodeType;
		unsigned int key;
};


#endif /* INFORMATION_H_ */
