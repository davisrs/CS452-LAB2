//the god damn Shader Loader Program
//By Richard Davis: Computer Engineer Clarkson university Spring 2014
//CU # 0207763

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

}//Close the angel namespace block

