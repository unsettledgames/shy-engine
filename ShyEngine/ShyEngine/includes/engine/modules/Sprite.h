#pragma once

#include <data/Texture.h>
#include <rendering/ShaderProgram.h>
#include <glm/glm.hpp>
#include <string>

namespace ShyEngine
{
	class Sprite
	{
		private:
			Texture m_texture;
			ShaderProgram m_shader;

		public:
			Sprite();
			Sprite(Texture& texture, ShaderProgram& shader);
			Sprite(const std::string& texturePath, ShaderProgram& shader);

			int attachShader(ShaderProgram& shader);
			int attachTexture(Texture& texture);
			int attachTexture(const std::string& texturePath);
	};
}