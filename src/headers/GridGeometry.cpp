#ifndef VISUALGRID
#define VISUALGRID
class VisualGrid{
	private:
		int* indices;
		int indexCount;
	public:
		//Returns pointer to array of indices
		int* WeldPoints(int* points);
		//Returns indices to buffers
		int* prepRender();
		//Uses already bound shader program and passes in the points and indices
		void render(int vertexAttributeIndex);
		
};
#endif
#ifndef GRIDGEOMETRY_H
#define GRIDGEOMETRY_H
class GridGeomtry{
	private:
		int width;
		int height;
		int rows;
		int columns;
		int* points;
	public:
		GridGeomtry(int width, int height, int rows, int columns);
		~GridGeomtry();
		//Returns points
		int* generate();
};
#endif
