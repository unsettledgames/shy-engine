#include <string>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <Error.h>

/*
	OPTIMIZABLE: save compiled version of shaders, recompile only if necessary. Could be done via makefile?
*/

class ShaderProgram
{
private:
	int _nAttributes;

	GLuint _vertShaderID;
	GLuint _fragShaderID;
	GLuint _programID;

	void compileShader(const std::string& filePath, GLuint shaderID);

public:
	ShaderProgram();

	~ShaderProgram();

	void compileShaders(const std::string& vertPath, const std::string& fragPath);

	void linkShaders();

	void addAttribute(const std::string& name);

	void use();

	void unuse();
};