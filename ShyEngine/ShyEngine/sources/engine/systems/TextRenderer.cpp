#include <engine/systems/TextRenderer.h>

namespace ShyEngine
{
	TextRenderer::TextRenderer() : Renderer("SpriteRenderer")
	{
		createVertexArray();
	}

	void TextRenderer::updateModules(ShaderData shaderData)
	{
		Text* currText;
		std::vector<Glyph> glyphs = m_modulesToUpdate[0].getGlyphs();
		// OPTIMIZABLE: sort sprites by shaders? Organize batches by texture + shader
		// Rendering process
		begin();

		// OPTIMIZABLE: use the correct shader lol
		glyphs[0].useShader();

		for (auto _module : m_modulesToUpdate)
		{
			glyphs[0].getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);
			draw(dynamic_cast<Text*>(&_module));
		}

		end();
		render();

		glyphs[0].unuseShader();
	}

	void TextRenderer::draw(Text* toDraw)
	{
		addGlyphs(toDraw->getGlyphs());
	}

	void TextRenderer::addGlyphs(std::vector<Glyph> toAdd)
	{
		for (Glyph s : toAdd)
		{
			m_renderables.push_back(s);
			m_renderablesPointers.push_back(&s);
		}
	}
}