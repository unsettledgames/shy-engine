#pragma once

#include <ShyEngine/includes/engine/ShyEngine.h>

namespace SE = ShyEngine;

class CameraMover : public SE::UserScript
{
	private:
	public:
		CameraMover() {};

		void init() override;

		void update() override;
};