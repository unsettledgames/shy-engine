#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>

#define MS_PER_SEC	1000

namespace ShyEngine
{
	class FpsLimiter
	{
	private:
		float m_targetFps = 60;
		float m_currFps = 60;

		float m_targetFrameTime = MS_PER_SEC / m_targetFps;

		float m_currTicks = 0;
		float m_prevTicks = 0;

		Uint32 m_frameTime = 0;
		float m_deltaTime = 1;

		bool m_isLimitingFps = false;

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