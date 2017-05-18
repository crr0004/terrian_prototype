#include "geometry/moveable.hpp"
#include <fmt/format.h>
using namespace Geometry;

void Moveable::operation(){

}

int Moveable::visit(Moveable* node){
	fmt::print("In visit moveable node\n");

	return 0;
}
