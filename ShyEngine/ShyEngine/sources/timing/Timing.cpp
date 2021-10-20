#include <timing/Timing.h>
#include <iostream>

namespace ShyEngine
{
	FpsLimiter::FpsLimiter() {}

	void FpsLimiter::init(int fps)
	{
		m_prevTicks = SDL_GetTicks();
		setTargetFps(fps);
	}

	// IMPROVEMENT: fixed, deterministic timestep (https://gafferongames.com/post/fix_your_timestep/)
	void FpsLimiter::begin()
	{
		calculateFPS();

		// Start and end times of the frame
		// Computing delta time for the current frame
		const float DESIRED_FRAME_TIME = MS_PER_SEC / m_targetFps;
		this->m_deltaTime = (float)m_frameTime / (float)DESIRED_FRAME_TIME;

		if (m_isLimitingFps && 1000.0f / m_targetFps > m_frameTime)
			SDL_Delay(1000.0f / (m_targetFps - m_frameTime));
	}

	void FpsLimiter::setTargetFps(int fps)
	{
		m_targetFps = fps;
	}

	void FpsLimiter::calculateFPS()
	{
		// Computing FPS
		static int samples[10];
		static int sum = 0;
		static int index = 0;

		static const int N_SAMPLES = 10;

		m_currTicks = SDL_GetTicks();
		m_frameTime = m_currTicks - m_prevTicks;
		m_prevTicks = m_currTicks;

		samples[index] = m_frameTime;
		index = (index + 1) % N_SAMPLES;

		sum = 0;
		for (int i = 0; i < N_SAMPLES; i++)
			sum += samples[i];

		m_currFps = 1000.0f / ((float)sum / N_SAMPLES);
	}

	float FpsLimiter::getCurrentFps()
	{
		return this->m_currFps;
	}

	void FpsLimiter::toggleFpsLimiting(bool state)
	{
		this->m_isLimitingFps = state;
	}

	float FpsLimiter::getDeltaTime()
	{
		return m_deltaTime;
	}
}