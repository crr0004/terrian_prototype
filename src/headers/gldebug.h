#ifndef GLDEBUG_H
#define GLDEBUG_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
class glDebug{
public:
    glDebug(){};
   ~glDebug(){};
    //if you want you can rename myCallback; This is just an example
   static void APIENTRY myCallback(GLenum source,
                                   GLenum type,
                                   GLuint id,
                                   GLenum severity,
                                   GLsizei length,
                                   const GLchar *msg,
                                   GLvoid *data)
   {
	 using namespace std;
      //display warnings/errors however you like
     cout << "\n**********Debug Output**************"                 << endl;
     cout << "source: "     << getStringForSource(source)     << endl;
     cout << "type: "       << getStringForType(type)         << endl;
     cout << "severity: "   << getStringForSeverity(severity) << endl;
     cout << "debug call: " << msg                                    << endl;
     cout << "\n************************" << endl;
	 if(type == GL_DEBUG_TYPE_ERROR){
		 exit(1);
	 }
   }
 
  private:
     //Parsing code from OpenGL Shader Language CookBook SE
     //https://github.com/daw42/glslcookbook
   static const char* getStringForType(GLenum type)
   {
     switch (type)
     {
        case GL_DEBUG_TYPE_ERROR:
              return"Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
              return "Deprecated behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
              return "Undefined behavior";
        case GL_DEBUG_TYPE_PORTABILITY:
              return "Portability issue";
        case GL_DEBUG_TYPE_PERFORMANCE:
              return "Performance issue";
        case GL_DEBUG_TYPE_MARKER:
              return "Stream annotation";
        case GL_DEBUG_TYPE_OTHER_ARB:
              return "Other";
        default:
              return "";
     }
   }
 
   static const char* getStringForSource(GLenum source)
   {
     switch (source)
     {
       case GL_DEBUG_SOURCE_API:
            return "API";
       case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "Window system";
       case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "Shader compiler";
       case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "Third party";
       case GL_DEBUG_SOURCE_APPLICATION:
            return "Application";
       case GL_DEBUG_SOURCE_OTHER:
            return "Other";
       default:
            return "";
     }
   }
 
   static const char* getStringForSeverity(GLenum severity)
   {
     switch (severity)
     {
      case GL_DEBUG_SEVERITY_HIGH:
           return "High";
      case GL_DEBUG_SEVERITY_MEDIUM:
           return "Medium";
      case GL_DEBUG_SEVERITY_LOW:
           return "Low";
      case GL_DEBUG_SEVERITY_NOTIFICATION:
           return "Notification";
      default:
           return("");
      }
   }
 
 };
#endif
