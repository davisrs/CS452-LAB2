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

// Big thanks to Google, Alexander Macri (Alex), and the Angel book!

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
	fprintf(stderr,"Sorry. Was unable to open file '%s' Does it exist?\n",shaderFile);
	return NULL; }
	
	//neat way to get the length of the file
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	//allocates memory for the file and reads in the file
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);
	
	if(ftell(fp) == 0){//checks to see if the file is empty
		fprintf(stderr, "File '%s' is empty.\n",shaderFile);
		return NULL;
	}

	buf[size] = '\0';//neat way to set a '\0' (null terminator) at end of file
	fclose(fp);//closes the file

	return buf;
	//ALEX's NOTE: if the file is unable to open or is empty this function will segmentation fault your program
}

