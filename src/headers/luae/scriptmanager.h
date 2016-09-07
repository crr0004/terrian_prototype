#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
/*
class MatrixStackSingleton{
	public:
		static MatrixStackSingleton* instance();
		glm::mat4 push(glm::mat4 m);
		glm::mat4 pop();
	protected:
		MatrixStackSingleton();
		~MatrixStackSingleton();
	private:
		static MatrixStackSingleton* _instance;
};
*/
class ScriptManager{
	public:
		static ScriptManager* instance();
	protected:
		ScriptManager();
		~ScriptManager();
	private:
		static ScriptManager* _instance;

};

#endif // !SCRIPTMANAGERSINGLETON_H
