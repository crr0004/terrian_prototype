#ifndef GEOMETRYLINE_H
#define GEOMETRYLINE_H
#include "geometry/point.h"
namespace Geometry{

	class Line{
		public:
			Line();
			Line(Point a, Point b);
			~Line();
	};
}
#endif
