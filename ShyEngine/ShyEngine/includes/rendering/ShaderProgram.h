#pragma once

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <util/Error.h>
#include <data/ImageLoader.h>
#include <data/Texture.h>
#include <glm/glm.hpp>

/*
	OPTIMIZABLE: save compiled version of shaders, recompile only if necessary. Could be done via makefile?
	OPTIMIZABLE: ShaderPrograms should probably be a property of each renderer.
*/

namespace ShyEngine {
	class ShaderProgram
	{
	private:
		int m_nAttributes = 0;

		GLuint m_vertShaderID = 0;
		GLuint m_fragShaderID = 0;
		GLuint m_programID = 0;

		void compileShader(const std::string& filePath, GLuint shaderID);

	public:
		ShaderProgram();

		~ShaderProgram();

		void compileShaders(const std::string& vertPath, const std::string& fragPath);

		void linkShaders();

		void addAttribute(const std::string& name);

		GLuint getUniformLocation(const std::string& name);

		void setOrthoProjection(const std::string& uniform, glm::mat4 val);

		void use(float time);

		void unuse();
	};
}