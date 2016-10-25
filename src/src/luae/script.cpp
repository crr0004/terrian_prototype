#include <lua/lua.hpp>
#include "luae/script.hpp"
#include <stdio.h>
#include <cstring>
#include "terrian_config.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second
using namespace Luae;

Script::Script(){

}

Script::Script(const char* scriptName){
	this->scriptName = scriptName;

}

Script::~Script(){

}

Script* Script::Load(const char* fileName){


	Script* result; 
	//const char* filePath = concat(xstr(SCRIPTS_DIR), "hello");
	//printf("%s\n", strcat(xstr(SCRIPTS_DIR), fileName));
	
	result = new Script();
	return result;
}
