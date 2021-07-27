#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

namespace ShyEngine
{
	class FpsLimiter
	{
	private:
		float _targetFps;
		float _currFps;

		float _startTicks;
		Uint32 _frameTime;

		void calculateFPS();

	public:
		FpsLimiter();

		/*
			Call init to set the target FPS
		*/
		void init(int fps);

		/*
			Call begin to mark the beginning of a frame
		*/
		void begin();

		/*
			Call end to mark the end of a frame and get the FPS
		*/
		float end();

		/*
			Get and set the target FPS
		*/
		void setTargetFps(int fps);
		float getCurrentFps();
	};
}