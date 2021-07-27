#include <Timing.h>

namespace ShyEngine
{
	FpsLimiter::FpsLimiter()
	{

	}

	void FpsLimiter::init(int fps)
	{
		setTargetFps(fps);
	}

	void FpsLimiter::begin()
	{
		// Start and end times of the frame
		_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::end()
	{
		Uint32 frameTicks = SDL_GetTicks() - _startTicks;

		calculateFPS();

		if (1000.0f / _targetFps > frameTicks)
			SDL_Delay(1000.0f / (_targetFps - frameTicks));

		return this->_currFps;
	}

	void FpsLimiter::setTargetFps(int fps)
	{
		this->_targetFps = fps;
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
		_frameTime = currTicks - prevTicks;
		sum += _frameTime;
		prevTime = _frameTime;
		timeIndex++;

		// Computing FPS
		_currFps = (1000.0f / (sum / NUM_SAMPLES));
		prevTicks = currTicks;
	}

	float FpsLimiter::getCurrentFps()
	{
		return this->_currFps;
	}
}