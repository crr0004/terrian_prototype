#ifndef DYNAMICS_NODE_H
#define DYNAMICS_NODE_H
#include "node.hpp"
namespace Dynamics {
	class DynamicNode : public Node{
		public:
			DynamicNode();
			virtual int visit(DynamicNode*);
			virtual int visit(INode*);
			virtual void step(double t, double dt);

	};
		
} // namespace Dynamics
#endif
