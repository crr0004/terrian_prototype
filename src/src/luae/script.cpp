#include <lua/lua.hpp>
#include <string>
#include <fstream>
#include <fmt/format.h>
#include "luae/scriptmanager.hpp"
#include "luae/script.hpp"
#include "terrian_config.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second
using namespace Luae;

Script::Script(){
	this->scriptName = 0;

}

Script::Script(const char* scriptName){
	this->scriptName = scriptName;

}

Script::~Script(){
	//delete scriptName;

}

Script* Script::Load(const std::string& fileName){
	Script* result = 0; 
	std::string* scriptPath = new std::string(xstr(SCRIPTS_DIR));
	scriptPath->append("/");
	scriptPath->append(fileName);
	std::fstream fs;
	//Try to open it
	fs.open(scriptPath->c_str());
	
	//did it work?
	if(fs.is_open()){
		result = new Script(fileName.c_str());
		fs.close();
	}
	delete scriptPath;
	return result;
}

const char* Script::getScriptName(){
	return this->scriptName;
}

void Script::loadScript(){
	if(this->scriptName == 0){
		fmt::print(stderr, "Script name isn't set. Can't load");
	}else{
		lua_State* lua = ScriptManager::instance()->getState();
		//TODO Probably should be cached somewhere
		std::string* scriptPath = new std::string(xstr(SCRIPTS_DIR));
		scriptPath->append("/");
		scriptPath->append(this->scriptName);
		if (luaL_loadfile(lua, scriptPath->c_str()) != 0) {
			fmt::print(stderr, "lua couldn't parse '{}': {}.\n", this->scriptName, lua_tostring(lua, -1));
		}
		delete scriptPath;

	}
}

bool Script::has(const char* functionName){
	this->loadScript();
	lua_State* lua = ScriptManager::instance()->getState();

	lua_pcall(lua, 0, 0, 0);
	lua_getglobal(lua, functionName);
	if(lua_isfunction(lua, -1) == 1){
		return true;
	}

	return false;
}

bool Script::call(const char* functionName){
	this->loadScript();
	lua_State* lua = ScriptManager::instance()->getState();
	bool result = false;

	lua_pcall(lua,0,0,0);
	lua_getglobal(lua,functionName);
	if(lua_isfunction(lua, -1) == 1){
		if (lua_pcall(lua, 0, 0, 0) == 0) {
			result = true;
		}else{
			fmt::print(stderr, "lua couldn't call {}: {}.\n", functionName, lua_tostring(lua, -1));
		}
	}
	return result;
}
