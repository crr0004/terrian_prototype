#ifndef ADDTODRAWQUEUECOMMAND_H
#define ADDTODRAWQUEUECOMMAND_H
#include <vector>
#include "patterns/command.hpp"
#include "polygon.hpp"
class AddToDrawQueueCommand : public Command{
	public:
		static void SetQueue(std::vector<Geometry::Polygon*>*);
		AddToDrawQueueCommand(Geometry::Polygon*);
		~AddToDrawQueueCommand();
		void execute();
	private:
		static std::vector<Geometry::Polygon*>* queue;
		Geometry::Polygon* drawHost;


};
#endif
