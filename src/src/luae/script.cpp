#include <lua/lua.hpp>
#include <string>
#include <fstream>
#include <fmt/format.h>
#include "luae/scriptmanager.hpp"
#include "luae/script.hpp"
#include "luae/Utilities.hpp"
#include "terrian_config.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second
using namespace Luae;


Script* Script::Load(const char* name, const char* sourceChunk){
	Script* result = 0; 
	result = new Script(name);
	result->sourceChunk = sourceChunk;
	result->sourceType = SCRIPT_SOURCE_CHUNK;
	result->loadScript();
	return result;
}

Script* Script::Load(const std::string fileName){

	return Script::Load(fileName.c_str());
}

Script* Script::Load(const char* fileName){
	Script* result = 0; 
	std::string* scriptPath = new std::string(xstr(SCRIPTS_DIR));
	scriptPath->append("/");
	scriptPath->append(fileName);
	std::fstream fs;
	//Try to open it
	fs.open(scriptPath->c_str());
	
	//did it work?
	if(fs.is_open()){
		result = new Script(fileName);
		result->sourceType = SCRIPT_SOURCE_FILE;
		fs.close();
		result->loadScript();
	}else{
		fmt::print(stderr, "Couldn't find script {}.\n", fileName);
	}
	delete scriptPath;
	return result;
}

void Script::loadFileScript(){
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
		}else{
			lua_pcall(lua,0,0,0);
		}
		delete scriptPath;

	}

}

void Script::loadChunkScript(){
	if(this->scriptName == 0){
		fmt::print(stderr, "Script name isn't set. Can't load");
	}else{
		lua_State* lua = ScriptManager::instance()->getState();
		//TODO Probably should be cached somewhere
		if (luaL_loadstring(lua, sourceChunk) != 0) {
			fmt::print(stderr, "lua couldn't parse '{}': {}.\n", this->scriptName, lua_tostring(lua, -1));
		}else{
			lua_pcall(lua,0,0,0);
		}
	}

}

void Script::loadScript(){
	lua_State* lua = ScriptManager::instance()->getState();
	//Clean the global environment so we can capture what the script does
	//int stackTop = lua_gettop(lua);
	lua_createtable(lua, 0, 0);
	lua_rawseti(lua, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	switch (sourceType) {
		case SCRIPT_SOURCE_FILE:
			loadFileScript();
			break;
		case SCRIPT_SOURCE_CHUNK:
			loadChunkScript();
			break;
		case SCRIPT_SOURCE_NONE:
			break;
	}
	//Copy the changes the script made
	lua_pushglobaltable(lua);
	ref = luaL_ref(lua, LUA_REGISTRYINDEX);
	//Restore original global table
	ScriptManager::instance()->RestoreGlobalTable();
	//lua_pop(lua, lua_gettop(lua) - stackTop);

}

Script::Script(){
	this->scriptName = 0;
	ref = -1;
}

Script::Script(const char* scriptName){
	this->scriptName = scriptName;
	ref = -1;
}

Script::~Script(){
	//delete scriptName;

}

const char* Script::getScriptName(){
	return this->scriptName;
}

bool Script::has(const char* functionName){
	lua_State* lua = ScriptManager::instance()->getState();
	bool result = false;

	this->push();
	lua_pcall(lua, 0, 0, 0);
	lua_getglobal(lua, functionName);
	if(lua_isfunction(lua, -1) == 1){
		result = true;
	}
	this->pop();

	return result;
}

bool Script::call(const char* functionName, int nargs, int nresults){
	lua_State* lua = ScriptManager::instance()->getState();
	bool result = false;

	this->push();
	lua_getglobal(lua,functionName);
	if(lua_isfunction(lua, -1) == 1){
		if (lua_pcall(lua, nargs, nresults, 0) == 0) {
			result = true;
		}else{
			fmt::print(stderr, "lua couldn't call {}: {}.\n", functionName, lua_tostring(lua, -1));
		}
	}
	this->pop();
	return result;

}

bool Script::call(const char* functionName){
	return this->call(functionName, 0, 0);
}

/* -------------------------------*/
/** 
 * @brief Saves the state of lua
 */
/* ---------------------------------*/
void Script::pop(){
	ScriptManager::instance()->RestoreGlobalTable();
	//fmt::print("Lua stack\n");
	//lua_getglobal(lua, "header");
	//lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
	/*
	lua_getfield(lua, -1, "functions");
	//PrintTable(lua);
	lua_pushstring(lua, "update2");
	lua_gettable(lua, -2);
	lua_pcall(lua,0,0,0);
	lua_Debug ar;
     lua_getinfo(lua, ">nS", &ar);
     printf("%s %d\n",ar.namewhat, ar.linedefined);
	 */
	//PrintGlobalTable(lua);
}
void Script::push(){
	lua_State* lua = ScriptManager::instance()->getState();
	lua_pushglobaltable(lua);
	lua_rawgeti(lua, LUA_REGISTRYINDEX, ref);
	luae_copytable(lua, -2, -1);
	lua_rawseti(lua, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_pop(lua,1);
}
