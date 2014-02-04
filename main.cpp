// http://www.arcsynthesis.org/gltut/index.html
// The framework file expects 5 functions to be defined: defaults, init, display, reshape, and keyboard
#include <iostream>
using namespace std;

#include "vg1.h";
#include "LoadShaders.h";

enum VAO_IDS { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumVAOs };
enum Attrib_IDs { vPosition = 0 };

GLUint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLunint NumVertices = 6;

///////////////////////////////////////////////////////////////////////////////
//	init
///////////////////////////////////////////////////////////////////////////////
init (void)
{
	glGenVertexArrays(NumVAOs, VAO);
	glBindVertexArray(VAOs[Triangles]);
	
	GLf
}

///////////////////////////////////////////////////////////////////////////////
//	display
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//	main
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char**argv){
	glutInit(&argc,argv);//initialize the GLUT library
	glutInitDisplayMode(GLUT_RGBA);//configures window to use RGBA
	glutInitWindowSize(512,512);//The window is 512 x 512
	glutInitContextVersion(4,3);//use openGL 4.3...
	glutInitContextProfile(GLUT_CORE_PROFILE);//...core profile as the context
	glutCreateWindow(argv[0]);//create the window
	if (glewInit()) {//see if GLEW (Extension wrangler) initialized
		cerr<<"Unable to initialize GLEW...exiting"<<endl;//Display this error if it didn't'
		exit(EXIT_FAILURE);//exit in failure
	}
	//NOW The interesting stuff happens
	init();//initialize all relevant openGL data
	glutDisplayFunc(display);//set up display callback, used to update the window,
					//provide the GLUT library a pointer to a function
	glutMainLoop();//an infinite loop for animation and input
}
