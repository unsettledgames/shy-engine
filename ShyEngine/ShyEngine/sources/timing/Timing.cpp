#include <timing/Timing.h>

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
		// Start and end times of the frame
		m_currTicks = SDL_GetTicks();
		m_frameTime = m_currTicks - m_prevTicks;
		m_prevTicks = m_currTicks;

		// Computing delta time for the current frame
		const float DESIRED_FRAME_TIME = MS_PER_SEC / m_targetFps;
		this->m_deltaTime = (float)m_frameTime / (float)DESIRED_FRAME_TIME;
	}

	float FpsLimiter::end()
	{
		Uint32 frameTicks = SDL_GetTicks() - m_currTicks;

		calculateFPS();

		if (m_isLimitingFps)
		{
			if (1000.0f / m_targetFps > frameTicks)
				SDL_Delay(1000.0f / (m_targetFps - frameTicks));
		}

		return this->m_currFps;
	}

	void FpsLimiter::setTargetFps(int fps)
	{
		m_targetFps = fps;
	}

	void FpsLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float prevTime = 0;
		static float sum = 0;
		static int timeIndex = 0;

		static Uint32 prevTicks = SDL_GetTicks();
		Uint32 currTicks = SDL_GetTicks();

		// Removing the last amount if I have more than NUM_SAMPLES frames
		if (timeIndex >= NUM_SAMPLES)
			sum -= prevTime;

		// Adding the new frame time
		m_frameTime = currTicks - prevTicks;
		sum += m_frameTime;
		prevTime = m_frameTime;
		timeIndex++;

		// Computing FPS
		m_currFps = (1000.0f / (sum / NUM_SAMPLES));
		prevTicks = currTicks;
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