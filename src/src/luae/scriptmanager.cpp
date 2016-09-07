#include "luae/scriptmanager.h"
#include <lua/lua.hpp>
#include "terrian_config.h"

ScriptManager* ScriptManager::_instance = 0;


ScriptManager::ScriptManager(){

}

ScriptManager::~ScriptManager(){
}

ScriptManager* ScriptManager::instance(){
	if(ScriptManager::_instance == 0){
		_instance = new ScriptManager();
	}

	return _instance;

}
