#ifndef GAMEFACADE_H
#define GAMEFACADE_H
#include "facade/line.h"
#include "geometry/line.h"

class GameFacade {

	public:
		static GameFacade* instance();
		Facade::Line* createLine(Geometry::Line line);

	protected:
		GameFacade();
		~GameFacade();
	private:
		static GameFacade* _instance;

};
#endif
