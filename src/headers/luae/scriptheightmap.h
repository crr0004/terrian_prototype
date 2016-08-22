#ifndef SCRIPTHEIGHTMAP_H
#define SCRIPTHEIGHTMAP_H
#include <lua/lua.hpp>
namespace Luae {
	/* -------------------------------*/
	/**
	 * @brief A adapter class for heightmap class to lua
	 */
	 /* ---------------------------------*/
	class ScriptHeightMap {
	public:
		ScriptHeightMap();
		~ScriptHeightMap();
		static ScriptHeightMap* instance();
		void bind(lua_State* l);
	private:
		static ScriptHeightMap* _instance;

	};
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
}

#endif 
