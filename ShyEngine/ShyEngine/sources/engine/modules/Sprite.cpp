#include <engine/modules/Sprite.h>
#include <engine/Entity.h>

namespace ShyEngine
{
	Sprite::Sprite() : Module("Sprite", nullptr) 
	{
	}

	Sprite::Sprite(Entity* entity, Texture& texture, ShaderProgram* shader, ColorRGBA8 color) : Module("Sprite", entity)
	{
		m_texture = texture;
		m_shader = shader;
		m_color = color;

		init();
	}

	Sprite::Sprite(Entity* entity, const std::string& texturePath, ShaderProgram* shader, ColorRGBA8 color) : 
		Module("Sprite", entity), Glyph(ResourcesManager.getTexture(texturePath), shader, color, 0.0f)
	{
		m_texture = ResourcesManager.getTexture(texturePath);
		m_shader = shader;
		m_color = color;

		init();
	}

	void Sprite::init() 
	{ 
		Transform transform = *(m_entity->getTransform());
		glm::vec2 pos = transform.getPos();
		glm::vec2 scale = transform.getScale();
		float angle = transform.getAngle();

		m_depth = 0.0f;
		m_pos = pos;
		m_scale = scale;

		// Get the corners
		glm::vec2 halfSize(scale.x / 2.0f, scale.y / 2.0f);
		glm::vec2 topLeft(-halfSize.x, halfSize.y);
		glm::vec2 topRight(halfSize.x, halfSize.y);
		glm::vec2 bottomRight(halfSize.x, -halfSize.y);
		glm::vec2 bottomLeft(-halfSize.x, -halfSize.y);

		// Rotate the points
		topLeft = Math::rotatePoint(topLeft, angle);
		topRight = Math::rotatePoint(topRight, angle);
		bottomRight = Math::rotatePoint(bottomRight, angle);
		bottomLeft = Math::rotatePoint(bottomLeft, angle) ;

		this->m_topLeft.color = m_color;
		this->m_topRight.color = m_color;
		this->m_bottomRight.color = m_color;
		this->m_bottomLeft.color = m_color;

		// UV = (0, 0, 1, -1);
		this->m_topLeft.setPosition(pos.x + topLeft.x, pos.y + topLeft.y);
		this->m_topLeft.setUV(0, -1);

		this->m_bottomLeft.setPosition(pos.x + bottomLeft.x, pos.y + bottomLeft.y);
		this->m_bottomLeft.setUV(0, 0);

		this->m_topRight.setPosition(pos.x + topRight.x, pos.y + topRight.y);
		this->m_topRight.setUV(1, -1);

		this->m_bottomRight.setPosition(pos.x + bottomRight.x, pos.y + bottomRight.y);
		this->m_bottomRight.setUV(1, 0);
	}
	
	int Sprite::attachShader(ShaderProgram* shader)
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

	bool Sprite::checkCompatibility(std::vector<Module>& otherModules)
	{
		// There must exist a Transform component
		return std::find_if(otherModules.begin(), otherModules.end(), 
			[](Module other) { return other.getName() == "Transform";}) != otherModules.end();
	}

	bool Sprite::checkDependency(std::vector<Module>& otherModules)
	{
		// Nothing depends on Sprite, at the moment
		return true;
	}
}