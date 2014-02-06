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

//Typedefs:
// ShaderInfo is a struct consisting of: type (a GLenum, filename (a string of characters), and a GLuint (integer) named shader
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

//MINE

