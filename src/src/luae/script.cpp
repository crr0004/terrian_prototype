#include <lua/lua.hpp>
#include "luae/script.hpp"
#include <string>
#include <fmt/format.h>
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

Script* Script::Load(const std::string& fileName){


	Script* result; 
	//const char* filePath = concat(xstr(SCRIPTS_DIR), "hello");
	std::string* Script_Dir = new std::string(xstr(SCRIPTS_DIR));
	fmt::print("Script dir {}\n", Script_Dir->c_str());
	//printf("%s\n", strcat(xstr(SCRIPTS_DIR), fileName));
	
	result = new Script();
	return result;
}
