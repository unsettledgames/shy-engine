#include <engine/systems/TextRenderer.h>

namespace ShyEngine
{
	TextRenderer::TextRenderer() : Renderer("SpriteRenderer")
	{
		createVertexArray();
	}

	void TextRenderer::updateModules(ShaderData shaderData)
	{
		// OPTIMIZABLE: depth sorting
		begin();

		if (m_modulesPointers.size() > 0)
		{
			// DEBUG: find a shader to use
			Text* currText;
			std::vector<Glyph> glyphs = m_modulesPointers[0]->getGlyphs();

			for (auto _module : m_modulesPointers)
			{
				draw(dynamic_cast<Text*>(_module), shaderData);
			}

			end();

			// IMPROVEMENT: use the correct shader
			glyphs[0].useShader();
			glyphs[0].getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);

			render();

			glyphs[0].unuseShader();
		}		
	}

	void TextRenderer::draw(Text* toDraw, ShaderData shaderData)
	{
		// Add the glyphs of the current text
		addGlyphs(toDraw->getGlyphs(), shaderData);
	}

	void TextRenderer::addGlyphs(std::vector<Glyph> toAdd, ShaderData shaderData)
	{
		for (Glyph s : toAdd)
		{
			// Add the glyph only if it's visible. This is done per glyph instead of per text to save resources
			if (Collider2D::AABB(glm::vec4(s.getPosition(), s.getScale()), shaderData.cameraViewport))
			{
				m_renderables.push_back(s);
				m_renderablesPointers.push_back(&s);
			}
		}
	}
}