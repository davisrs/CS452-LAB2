// +Write a shader header file that you use to color a polygon.
// +Make sure you input the color into the shaders to color the polygon.
// +You can reference the shader programs from the books.
// +Make a header file that reads the shader file.
// +Make a function that reads the shader file.
// +Creates a shader program.
// +Attaches shader to shader program.
// +Links program.
// +Uses the shader program.
// +Write a step by step decription of the process in creating a shader program.

//This is the .h file, it contains function prototypes and typedefs for used by the myInitShaders.cpp file

//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __LOAD_SHADERS_H__
#define __LOAD_SHADERS_H__

#include <GL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//Typedefs:
// ShaderInfo is a struct consisting of: type (a GLenum, filename (a string of characters), and a GLuint (integer) named shader

//----------------------------------------------------------------------------
//
//  LoadShaders() takes an array of ShaderFile structures, each of which
//    contains the type of the shader, and a pointer a C-style character
//    string (i.e., a NULL-terminated array of characters) containing the
//    entire shader source.
//
//  The array of structures is terminated by a final Shader with the
//    "type" field set to GL_NONE.
//
//  LoadShaders() returns the shader program value (as returned by
//    glCreateProgram()) on success, or zero on failure. 
//
//----------------------------------------------------------------------------

typedef struct {
    GLenum       type;
    const char*  shaderFile;
    GLuint       shader;
} ShaderInfo;

GLuint LoadShaders( ShaderInfo* );

//function prototypes
GLuint createShader(GLenum type, const GLchar* shadeSource);
const GLchar* inputShader(const char* filename);
GLuint createProgram(const vector<GLuint> shadeList);

//Mine
const char* readShaderSource(const char* shaderFile)

//----------------------------------------------------------------------------

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __LOAD_SHADERS_H__

