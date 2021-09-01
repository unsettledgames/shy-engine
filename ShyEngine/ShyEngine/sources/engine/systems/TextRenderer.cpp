#include <engine/systems/TextRenderer.h>

namespace ShyEngine
{
	TextRenderer::TextRenderer() : Renderer("SpriteRenderer")
	{
		createVertexArray();
	}

	void TextRenderer::updateModules(ShaderData shaderData)
	{
		// OPTIMIZABLE: sort sprites by shaders? Organize batches by texture + shader
		// Rendering process
		begin();

		Text* currText;
		std::vector<Glyph> glyphs = m_modulesToUpdate[0].getGlyphs();

		for (auto _module : m_modulesToUpdate)
		{
			draw(dynamic_cast<Text*>(&_module));
		}

		end();

		// OPTIMIZABLE: use the correct shader lol
		glyphs[0].useShader();
		glyphs[0].getShader()->setOrthoProjection("orthoProj", shaderData.cameraMatrix);

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