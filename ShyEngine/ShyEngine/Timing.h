#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

#define MS_PER_SEC	1000

namespace ShyEngine
{
	class FpsLimiter
	{
	private:
		float _targetFps;
		float _currFps;

		float _startTicks;
		Uint32 _frameTime;
		Uint32 _deltaTime;

		bool _isLimitingFps;

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
			Toggle FPS limiting
		*/
		void toggleFpsLimiting(bool newState);

		/*
			Returns delta time
		*/
		float getDeltaTime();

		/*
			Get and set the target FPS
		*/
		void setTargetFps(int fps);
		float getCurrentFps();
	};
}