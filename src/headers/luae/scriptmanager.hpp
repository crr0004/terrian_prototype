#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
#include <lua/lua.hpp>
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
		lua_State* getState();
		void NewLib(const struct luaL_Reg lib[], const char* name);
	protected:
		ScriptManager();
		~ScriptManager();
	private:
		static ScriptManager* _instance;
		lua_State* state;

};

#endif // !SCRIPTMANAGERSINGLETON_H
