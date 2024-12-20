#include <GL/glew.h>

#include <vector>
#include <string>

GLuint MakeShader(GLuint t, std::string path);
GLuint AttachAndLink(std::vector<GLuint> shaders);