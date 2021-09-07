#pragma once

#include <data/Texture.h>
#include <rendering/ShaderProgram.h>
#include <glm/glm.hpp>
#include <string>
#include <data/Vertex.h>
#include <data/ColorRGBA8.h>
#include <data/ResourcesManager.h>
#include <data/Glyph.h>
#include <vector>
#include <engine/modules/Transform.h>
#include <util/Math.h>

namespace ShyEngine
{
	class SpriteRenderer;
	class TextRenderer;

	class Sprite : public Module, public Glyph
	{
		friend class SpriteRenderer;

		private:
			void updateVertices();

		public:
			Sprite();
			Sprite(Entity* entity, Texture& texture, ShaderProgram* shader,
				ColorRGBA8 color = ColorRGBA8(255, 255, 255, 255));
			Sprite(Entity* entity, const std::string& texturePath, ShaderProgram* shader, 
				ColorRGBA8 color = ColorRGBA8(255, 255, 255, 255));

			int attachShader(ShaderProgram* shader);
			int attachTexture(Texture& texture);
			int attachTexture(const std::string& texturePath);

			bool checkCompatibility(std::vector<Module>& otherModules);
			bool checkDependency(std::vector<Module>& otherModules);
	};
}