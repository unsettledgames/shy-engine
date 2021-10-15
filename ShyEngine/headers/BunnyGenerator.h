#pragma once

#include <ShyEngine/includes/engine/ShyEngine.h>

namespace SE = ShyEngine;

class BunnyGenerator : public ShyEngine::UserScript
{
	private:
		int m_currBunnies = 0;
		SE::Text* m_fpsCounter;

		SE::ShaderProgram* m_shader = nullptr;
		bool m_canGenerate = true;
		float nextBunnyTime = 0;

		void generateBunny();
	public:
		BunnyGenerator() {}

		void init() override;

		void update() override;
};