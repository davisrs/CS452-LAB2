//the god damn Shader Loader Program
//By Richard Davis: Computer Engineer Clarkson university Spring 2014


//Shaders are this mini programs that run on the GPU instead of CPU
//But we need to get them there
//So we need a loader function
//So lets make one

//First include Angel's Crazy Library because why not at this point?
#include "Angel.h" // His file

namespace Angel { //Honestly this scares me, last time it segfaulted

//We load our shader files as an array of characters AKA a string
//So lets make that string variable!
static char * //A static variable inside a function keeps its value between invocations //Honestly: Shouldn't there be a ; HERE?
readMeShaderFile(const char* shaderFileName){//The magic happens here
	//We are going to read that file and copy it into a wonderful string that gets returned to the program
	//Input:shaderFileName = the .glsl file on your hardrive that has your shader code in it... goes here
	//Output: buffy = the string that holds all that glsl code
	//Local Vars
	FILE* readFile //This is the stuff in file that gets made into our string
	long int size //This is the size of (num chars) that file -and hence in our char array/string //being long means its at least 32 bits--so we can have big files w/o issues
	char* buffy //This is our string of stuff in that file//Angel used buf, I'm way too tired right now.
	//Start coding
	readInFile = fopen(shaderFileName, "r");//open as read only, last thing we want to do is change anything //be sure to close this later
	if (readInFile == NULL ) { //If the file be empty
		return NULL;//return empty
		std::cerr << "ERROR: The file you gave me " << s.readFile << " was empty. WTF?";//and yell at the programmer
	}//Enough yelling

	fseek(readInFile, 0L, SEEK_END);//No binary header=No offset, Find the end of that File!
	size = ftell(readInFile);//get the size of that file
	
	fseek(readInFile,0L,SEEK_SET);//having read to the end, lets read it again more carefully-- this takes us back to the beginning of that file
	buffy = new char[size + 1];//allocate memory for the array of chars (named buffy -- I'm gonna regret this) which is the same size as the (file + 1)
	fread(buffy, 1, size, readInfile);//read an array of size (size) consisting of 1 byte chars from the readInFile and store it into a block of memory which is of at least size (size) of file (buffy!)
	buffy[size] = ' ';//make the very end of the buffer into a space (so we know when it ends?)
	fclose(readInFile);//WE ARE DONE with that physical file! CLOSE THE FILE before anything unexpected/ stupid happens

	return buffy;//Return a buffer that includes everything in that was in that file
}//End ze readMeShaderFile function

//Having the shader code in our buffer, we can use that to create GLSL program oobjects to invoke!

//Function #2
GLuint InitShader(const char* vShaderFileName, const char* fShaderFileName){
	//Given the names of our vertex and fragment shader files containing precious GLSL code on our hard drive, generate a GLSL program object!
        //Input:vShaderFileName = the .glsl file on your hardrive that has your vertex shader code in it... goes here
	//fShaderFileName = the .glsl file on your hardrive that has your fragment shader code in it... goes here
        //Output: GLuint program //the program object containing all of aour shaders!
        //Local Vars
	GLuint program //the program object which contains our shaders!
	const int numShaders = 2;//number of shaders in our array of shaders, typically 2, a vertex + a fragment shader
	GLuint shaderID = //this is the OpenGL shader object//is this that ShaderID object?
	//Structure of a Shader
	struct Shader {//Our typical shader consists of: //NOTE: does not contain OpenGL shader objects
		const char*	filename;//the name of it's GLSL file
		GLenum  	type;//Shader's type-- Usually this is either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
		GLchar*		source;//This is what is in the GLSL file, default to NULL before loading
	}//End Shader Structure
	shaders[numShaders] = {//Since we usually have 2 shaders, create an array of ...well... 2 shaders
		{ vShaderFileName, GL_VERTEX_SHADER, NULL }, //The Vertex Shader
		{ fShaderFileName, GL_FRAGMENT_SHADER, NULL  }//The Fragment Shader
	};//End array of shaders
	
	program = glCreateProgram ();//YES!creates an empty program object
	
	//increment through our array of shaders and load their actual values
	for ( int i = 0; i < numShaders; ++i) {//I learned something NEW! ++i != i++ apparently //EG i=0, x=i++ -> i=1, x=1 (post value of i) vs x=++i -> i=1, x=0 (pre value of i_) 
		Shader& s = shaders[i];//create a pointer to the ith shader in the array? -- named s for ease of typing
		s.source = readMeShaderFile(s.filename); //Swizzling is nice
		if ( s.source == NULL ) {//if the shader file is empty
			std:cerr << "Failed to read " << s.filename << std::endl;
			exit( EXIT_FAILURE );//Yell at the programmer and kill the process in FAILURE
		}//end if statement
		
		shaderID = glCreateShader(s.type);//Create an empty shader object of appropriate type specified in the Shader array and return a nonzero ID#
		glShaderSource(shaderID, 1, (const CLchar**) &s.source, NULL);//replace the source code in a the empty shader object handled by shaderID with the string of GLSL code in s.source
		glCompileShader( shaderID );//compiles the source code strings that have been stored in the shader object specified by shaderID

//Note: Compilation of a shader can fail for a number of reasons as specified by the OpenGL ES 
//Shading Language Specification. Whether or not the compilation was successful, information about the 
//compilation can be obtained from the shader object's information log by calling glGetShaderInfoLog

		GLint compiled;//
		glGetShaderiv( shaderID, GL_COMPILE_STATUS, &compiled );
	}//end for loop

}//End the InitShaderFunction


}//Close the angel namespace block

