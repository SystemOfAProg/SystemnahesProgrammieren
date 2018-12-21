#ifndef STRINGTABNODE_H_
#define STRINGTABNODE_H_

class StringTabNode {
	public:
		StringTabNode();
		virtual ~StringTabNode();
		char* getVector();
		void setNext(StringTabNode* next);
		StringTabNode* getNext();
		unsigned int getSize();
		void print();
	private:
		static const unsigned int STRING_TAB_NODE_SIZE = 1024;
		unsigned int tabNodeSize;
		StringTabNode* next;
		void init();
		char vector[STRING_TAB_NODE_SIZE];
};


#endif /* STRINGTABNODE_H_ */
