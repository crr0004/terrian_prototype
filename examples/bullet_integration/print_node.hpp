#ifndef PRINT_NODE_H
#define PRINT_NODE_H
#include "node.hpp"
class PrintNode : public Node {
	public:
		PrintNode();
		virtual int visit(INode* node);
		virtual int visit(PrintNode* node);
};
#endif
