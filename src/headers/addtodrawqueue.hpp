#ifndef ADDTODRAWQUEUECOMMAND_H
#define ADDTODRAWQUEUECOMMAND_H
#include <vector>
#include "patterns/command.hpp"
#include "IPolygon.hpp"
class AddToDrawQueueCommand : public Command{
	public:
		static void SetQueue(std::vector<IPolygon*>*);
		AddToDrawQueueCommand(IPolygon*);
		~AddToDrawQueueCommand();
		void execute();
	private:
		static std::vector<IPolygon*>* queue;
		IPolygon* drawHost;


};
#endif
