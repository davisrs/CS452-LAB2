// Programmer: Richard Sean Davis
// Assignment:Lab2
//
// Objectives:
//
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

// This is the .cpp file it contains the actual code for the functions in the myInitShaders.h file

// Big thanks to Google, Alexander Macri (Alex), and the Edward Angel (blue) book!

//All the includes
#ifndef INITSHADERS_H_
#define INITSHADERS_H_

//#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "GL/glu.h"

#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

//function prototypes
GLuint createShader(GLenum type, const GLchar* shadeSource);
const GLchar* inputShader(const char* filename);
GLuint createProgram(const vector<GLuint> shadeList);

typedef struct {
    GLenum       type;// GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    const char*  shaderFile;//name of file to input
    //GLuint       shader;
} ShaderInfo;

GLuint LoadShaders( ShaderInfo* );

//Mine
//const char* readShaderSource(const char* shaderFile)

//My Code (based on alex and Angel's' textbook's example')
static char*
readShaderSource(const char* shaderFile)//this funtion loads the shader from the vertex.glsl and fragments.glsl shader files
						    //  and returns a string (buf) containing all the chars from the .glsl files
						    //  with a null terminator /0 at the end of the array
{
    FILE* fp = fopen(shaderFile, "r");//opens the file
    	//If you want to portably read/write text files on any system, use "r", and "w" in fopen(). 
    	//That will guarantee that the files are written and read properly. 
    	//If you are opening a binary file, use "rb" and "wb", so that an unfortunate newline-translation doesn't mess your data.
    	//SOURCE:http://stackoverflow.com/questions/2174889/whats-the-differences-between-r-and-rb-in-fopen

    if ( fp == NULL ) {//check to see if file is opened
	fprintf(stderr,"Sorry. Was unable to open file '%s' Does it even exist?\n",shaderFile);
	return NULL; }
	
	//neat way to get the length of the file
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	//allocates memory for the file and reads in the file
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);
	
	if(ftell(fp) == 0){//checks to see if the file is empty
		fprintf(stderr, "Sorry. This file you gave me: '%s' is empty. WTF?\n",shaderFile);
		return NULL;
	}

	buf[size] = '\0';//neat way to set a '\0' (null terminator) at end of file
	fclose(fp);//closes the file

	return buf;
	//ALEX's NOTE: if the file is unable to open or is empty this function will segmentation fault your program
}

//Compile those individual parts that we read to create a GLSL program object from fagment and shader files in buf

void InitShader(ShaderInfo* shaders)//Pass in the list of shaders so we can have more than just fragment and vertex
{
	ShaderInfo* shade=shaders;
	vector<GLuint> Shadelist;//initialize list of shaders
	
	while(shade->type != GL_NONE){//loop through all the shaders in the list
		Shadelist.push_back(createShader(shade->type,inputShader(shade->shaderFile)));//adding shaders into the list
		++shade;//incrementation
	}
	GLuint program=createProgram(Shadelist);//creates the program linking to all the shaders  
	glUseProgram(program);//installs a program object as part of current rendering state
}

//this function create your shader
GLuint createShader(GLenum type, const GLchar* shadeSource){
  
  GLuint shader = glCreateShader(type);//create shader based on type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
  glShaderSource(shader, 1, &shadeSource, NULL);//loads the source code of the file into the shader
  
  glCompileShader(shader);//compiles a shader object
  
  GLint compileStatus;//status of the compilation variable
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);//returns the comiple status into the variable
  
  if(!compileStatus){//checks to see if the shader compiled
    GLint logSize;//variable for size of the debug info
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);//returns the size of the the source file into the variable
    
    GLchar* infoLog = new GLchar[logSize+1];//allocating memory for the debug info
    glGetShaderInfoLog(shader,logSize,&logSize,infoLog);//returns the error messages into the variable infoLog
    
    const char *shadeInfo= NULL;//char array for what shader that is having an error
    switch(type){//way to get what shader has the error
      case GL_VERTEX_SHADER: shadeInfo = "vertex"; break;
      case GL_GEOMETRY_SHADER_EXT: shadeInfo = "geometric"; break;
      case GL_FRAGMENT_SHADER: shadeInfo = "fragment"; break;
    }
    fprintf(stderr,"\nCompile failure in %u shader: %s\n Error message:\n%s\n",type,shadeInfo,infoLog);//prints information need to debug shaders
    delete[] infoLog;//memory management
  }
  return shader;//self explanatory
}

//this function creates the shading program we are going to link the shader too
GLuint createProgram(const vector<GLuint> shadeList){

  GLuint program = glCreateProgram();//creates your program
  
  for(GLuint i=0;i<shadeList.size();i++){glAttachShader(program,shadeList[i]);}//attaches shaders to program
  
  glBindAttribLocation(program, 0, "in_position");//binds the location an attribute to a program
  glBindAttribLocation(program, 1, "in_color");//binds the location an attribute to a program
  glLinkProgram(program);//links program to your program //weird
  
  GLint linkStatus;//status for linking variable
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);//returns the status of linking the program into the variable
  
  if(!linkStatus){//checks to see if your program linked to the program
    GLint logSize;//variable for size of the debug info
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);//returns the linking status into the variable
    
    GLchar *infoLog = new GLchar[logSize+1];//allocating memory for the debug info
    glGetProgramInfoLog(program,logSize,&logSize,infoLog);//returns the error messages into the variable infoLog
    
    fprintf(stderr,"\nShader linking failed: %s\n",infoLog);//prints your linking failed
    delete[] infoLog;//memory management
    
    for(GLuint i=0;i<shadeList.size();i++){glDeleteShader(shadeList[i]);}//memory management
  }
  return program;//self explanatory
}

//DONE!
#endif
