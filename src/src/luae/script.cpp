#include <lua/lua.hpp>
#include <string>
#include <fstream>
#include <fmt/format.h>
#include "luae/script.hpp"
#include "terrian_config.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second
using namespace Luae;

Script::Script(){
	this->scriptName = '\0';

}

Script::Script(const char* scriptName){
	this->scriptName = scriptName;

}

Script::~Script(){

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
		fmt::print("File {} exists", scriptPath->c_str());
		result = new Script(fileName.c_str());
	}
	return result;
}

const char* Script::getScriptName(){
	return this->scriptName;
}

bool Script::has(const char* functionName){

	return false;

}
