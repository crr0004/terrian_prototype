#ifndef VISUALSERVER_H
#define VISUALSERVER_H 
class VisualServer{
	public:
		static VisualServer* Instance();
		
		//void renderIndexTriangleSurface(VisualSurface* surface);
	protected:
		VisualServer();
	private:
		static VisualServer* _instance;

};
#endif
