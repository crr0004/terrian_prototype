#ifndef DYNAMICS_DRIVER_H
#define DYNAMICS_DRIVER_H
#include "node.hpp"
#include "dynamics/dynamic_node.hpp"
namespace Dynamics {
	class DynamicDriver : public Node{
		public:
			DynamicDriver();
			virtual void operation();
			virtual void add(INode*);
			virtual void add(DynamicNode*);
			virtual int visit(INode*);
			virtual int visit(DynamicNode*);
		private:
			double frameTime,t,dt,accumulator;
	};
	
} // namespace Dynamics
#endif
