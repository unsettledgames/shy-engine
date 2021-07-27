#include <ShaderProgram.h>

namespace ShyEngine {
	ShaderProgram::ShaderProgram() : _nAttributes(0), _vertShaderID(0), _fragShaderID(0), _programID(0)
	{

	}

	ShaderProgram::~ShaderProgram()
	{

	}

	void ShaderProgram::setOrthoProjection(const std::string& uniform, glm::mat4 val)
	{
		GLint orthoProjLocation = getUniformLocation("orthoProj");
		glUniformMatrix4fv(orthoProjLocation, 1, GL_FALSE, &(val[0][0]));
	}

	GLuint ShaderProgram::getUniformLocation(const std::string& name)
	{
		GLint location = glGetUniformLocation(_programID, name.c_str());

		if (location == GL_INVALID_INDEX)
			Error::fatal("Couldn't get uniform " + name + " location");

		return location;
	}

	void ShaderProgram::use(float time)
	{
		glUseProgram(_programID);

		for (int i = 0; i < _nAttributes; i++)
			glEnableVertexAttribArray(i);

		glActiveTexture(GL_TEXTURE0);

		// Applying texture
		GLuint textureLocation = getUniformLocation("mainTexture");
		glUniform1i(textureLocation, 0);

		// Applying time
		GLint timeLocation = getUniformLocation("time");
		glUniform1f(timeLocation, time);
	}

	void ShaderProgram::unuse()
	{
		glUseProgram(0);

		for (int i = 0; i < _nAttributes; i++)
			glDisableVertexAttribArray(i);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void ShaderProgram::linkShaders()
	{
		// Link our program
		glLinkProgram(_programID);

		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked != GL_TRUE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertShaderID);
			glDeleteShader(_fragShaderID);

			Error::fatal("Shaders failed to link");
			std::printf("%s\n", &(infoLog[0]));
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programID, _vertShaderID);
		glDetachShader(_programID, _fragShaderID);
		glDeleteShader(_vertShaderID);
		glDeleteShader(_fragShaderID);
	}

	void ShaderProgram::addAttribute(const std::string& name)
	{
		glBindAttribLocation(_programID, _nAttributes, name.c_str());
		_nAttributes++;
	}

	/*
		REFACTOR: shaders should be added by the user, so they should probably also call compileShaders
		on their own OR maybe have an Engine.init() that compiles shaders and also does other stuff.
		I'd like to hide what is actually happening behind the scenes.
	*/
	void ShaderProgram::compileShaders(const std::string& vertPath, const std::string& fragPath)
	{
		// Get a program object.
		_programID = glCreateProgram();

		// Creating shaders, handling errors
		_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertShaderID == 0)
			Error::fatal("Couldn't create vertex shader");

		_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragShaderID == 0)
			Error::fatal("Couldn't create fragment shader");

		// Compile shaders
		compileShader(vertPath, _vertShaderID);
		compileShader(fragPath, _fragShaderID);

		// Attach our shaders to our program
		glAttachShader(_programID, _vertShaderID);
		glAttachShader(_programID, _fragShaderID);
	}

	/*
		Compiles a single shader. OPTIMIZABLE: can't I just cache a compiled version of a shader so that 
		I can skip compilation?
	*/
	void ShaderProgram::compileShader(const std::string& filePath, GLuint shaderID)
	{
		// Shader compile error
		GLint compileError = 0;
		std::ifstream file(filePath);
		std::string currLine;
		std::string fileContent = "";

		// Handling file opening error
		if (file.fail())
			Error::fatal("Couldn't open shader file " + filePath);
		// Getting file contents
		while (std::getline(file, currLine))
			fileContent += currLine + "\n";
		file.close();

		// Setting the source for the shader
		const char* fileContentPointer = fileContent.c_str();
		glShaderSource(shaderID, 1, &fileContentPointer, nullptr);
		// Compiling the shader
		glCompileShader(shaderID);

		// Error checking
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileError);

		if (compileError != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(shaderID, 1024, &log_length, message);
			glDeleteShader(shaderID);

			Error::fatal("Shader " + filePath + " failed to compile: \n" + message);
		}
	}
}