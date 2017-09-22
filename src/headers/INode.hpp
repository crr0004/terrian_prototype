#ifndef COLLISION_INODE_H
#define COLLISION_INODE_H
class Command;
class Node;
class BulletNode;
namespace Geometry{
	class Moveable;
}
class INode{
	public:
		virtual void operation() = 0;
		virtual void add(INode*) = 0;
		virtual int insert(INode*) = 0;
		virtual void remove(int) = 0;
		virtual int getChildCount() = 0;
		virtual INode* getChild(int) = 0;
		virtual void setParent(INode*) = 0;
		virtual INode* getParent() = 0;
		virtual int visit(INode*) = 0;
		virtual int visit(Geometry::Moveable*){return -1;}
		virtual int visit(Node*){return -1;}
		virtual ~INode(){}
};
#endif //COLLISION_INODE_H
