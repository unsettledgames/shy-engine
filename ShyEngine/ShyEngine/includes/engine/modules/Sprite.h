#pragma once

#include <data/Texture.h>
#include <rendering/ShaderProgram.h>
#include <glm/glm.hpp>
#include <string>
#include <data/Vertex.h>
#include <data/ColorRGBA8.h>
#include <data/ResourcesManager.h>
#include <vector>
#include <engine/modules/Transform.h>
#include <util/Math.h>

namespace ShyEngine
{
	class SpriteRenderer;

	class Sprite : Module
	{
		friend class SpriteRenderer;
		friend bool operator==(const Sprite& s1, const Sprite& s2);

		private:
			Texture m_texture;
			ShaderProgram m_shader;

			Vertex m_topLeft;
			Vertex m_bottomLeft;
			Vertex m_topRight;
			Vertex m_bottomRight;

			ColorRGBA8 m_color;

			float m_depth;

			void init();

		public:
			Sprite();
			Sprite(const std::string& texturePath, ShaderProgram& shader, 
				ColorRGBA8 color = ColorRGBA8(255, 255, 255, 255));
			Sprite(const std::string& texturePath, const std::string& vertPath, const std::string& fragPath, 
				ColorRGBA8 color = ColorRGBA8(255, 255, 255, 255));

			int attachShader(ShaderProgram& shader);
			int attachTexture(Texture& texture);
			int attachTexture(const std::string& texturePath);

			bool checkCompatibility(std::vector<Module>& otherModules);
			bool checkDependency(std::vector<Module>& otherModules);
	};
}