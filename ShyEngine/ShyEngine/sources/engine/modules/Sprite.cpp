#include <engine/modules/Sprite.h>
#include <data/ResourcesManager.h>

namespace ShyEngine
{
	Sprite::Sprite() {}

	Sprite::Sprite(Texture& texture, ShaderProgram& shader)
	{
		m_texture = texture;
		m_shader = shader;
	}

	Sprite::Sprite(const std::string& texturePath, ShaderProgram& shader)
	{
		m_texture = ResourcesManager.getTexture(texturePath);
		m_shader = shader;
	}

	int Sprite::attachShader(ShaderProgram& shader)
	{
		m_shader = shader;
		return 0;
	}

	int Sprite::attachTexture(Texture& texture)
	{
		m_texture = texture;
		return 0;
	}

	int Sprite::attachTexture(const std::string& texturePath)
	{
		m_texture = ResourcesManager.getTexture(texturePath);
		return 0;
	}
}