#pragma once

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <Error.h>
#include <ImageLoader.h>
#include <Texture.h>

/*
	OPTIMIZABLE: save compiled version of shaders, recompile only if necessary. Could be done via makefile?
	OPTIMIZABLE: ShaderPrograms should probably be a property of each renderer.
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

	GLuint getUniformLocation(const std::string& name);

	void use(float time);

	void unuse();
};