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

//book
readShaderSource(const char* shaderFile)
{
    FILE* fp = fopen(shaderFile, "r");//opens the file
    	//If you want to portably read/write text files on any system, use "r", and "w" in fopen(). 
    	//That will guarantee that the files are written and read properly. 
    	//If you are opening a binary file, use "rb" and "wb", so that an unfortunate newline-translation doesn't mess your data.
    	//SOURCE:http://stackoverflow.com/questions/2174889/whats-the-differences-between-r-and-rb-in-fopen

    if ( fp == NULL ) {//check to see if file is opened
	fprintf(stderr,"unable to open file '%s'\n",filename);
	return NULL; }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
}

//alex
//this funtion loads the shader from the vertex, fragments shaders 
const GLchar* inputShader(const char* filename){

  FILE* fshade = fopen(filename, "rb");//opens file
  
  if(!fshade){//check to see if file is opened
    fprintf(stderr,"unable to open file '%s'\n",filename);
    return NULL;
  }
  
  //neat way to get the length of the file
  fseek(fshade, 0, SEEK_END);
  long filesize=ftell(fshade);
  fseek(fshade, 0, SEEK_SET);
  
  
  //allocates memory for the file and read in the file 
  GLchar* shadingSource= new GLchar[filesize+1];//
  fread(shadingSource, 1, filesize, fshade);
  
  
  if(ftell(fshade) == 0){//checks to see if the file is empty
    fprintf(stderr, "File '%s' is empty.\n",filename);
    return NULL;
  }

  fclose(fshade);//closes file
  
  shadingSource[filesize] = 0;//neat way to set a '\0' at end of file
  
  return const_cast<const GLchar*>(shadingSource);//overloads the const so the value with change per file  
  
  //NOTE: if the file is unable to open or is empty this function will segmentation fault your program
}
