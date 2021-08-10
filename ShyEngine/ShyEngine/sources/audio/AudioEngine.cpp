#include <audio/AudioEngine.h>
#include <util/Error.h>

namespace ShyEngine
{
	void SoundEffect::play(int loops /* = 0 */)
	{
		// IMPROVEMENT: -1 is the number of channels, could be nice to have some smart way to
		// select the right channel. Find a way to detect paused channels or something, in general have a 
		// look at how channels work
		if (Mix_PlayChannel(-1, m_chunk, loops) < 0)
			if (Mix_PlayChannel(0, m_chunk, loops) < 0)
				Error::fatal("Couldn't play sound effect");
	}

	void Music::play(int loops /* = 1 */)
	{
		if (Mix_PlayMusic(m_music, loops) < 0)
			Error::fatal("Couldn't play music");
	}

	void Music::pause()
	{
		Mix_PauseMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}

	AudioEngine::~AudioEngine()
	{
		destroy();
	}

	void AudioEngine::init()
	{
		if (!m_initialized)
		{
			// Combine MIX_INIT_FAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
			if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0)
				Error::fatal("Couldn't initialize audio engine (Mix_Init error: " + std::string(Mix_GetError()));
			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
				Error::fatal("Couldn't initialize audio engine (Mix_OpenAudio error: " + std::string(Mix_GetError()));

			m_initialized = true;
		}
		else
		{
			std::cout << "WARNING: tried to initialize the AudioEngine twice" << std::endl;
		}
	}

	void AudioEngine::destroy()
	{
		if (m_initialized)
		{
			m_initialized = false;

			for (auto& it : m_effectsCache)
				Mix_FreeChunk(it.second);
			for (auto& it : m_musicCache)
				Mix_FreeMusic(it.second);
			
			m_effectsCache.clear();
			m_musicCache.clear();

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& fileName)
	{
		SoundEffect ret;
		auto it = m_effectsCache.find(fileName);

		// The effect isn't cached, load it
		if (it == m_effectsCache.end())
		{
			Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());
			if (chunk == nullptr)
				Error::fatal("Couldn't load the effect at path " + fileName);

			m_effectsCache[fileName] = chunk;
			ret.m_chunk = chunk;
		}
		// Use the cached version
		else
			ret.m_chunk = it->second;

		return ret;
	}

	Music AudioEngine::loadMusic(const std::string& fileName)
	{
		Music ret;
		auto it = m_musicCache.find(fileName);

		// The effect isn't cached, load it
		if (it == m_musicCache.end())
		{
			Mix_Music* chunk = Mix_LoadMUS(fileName.c_str());
			if (chunk == nullptr)
				Error::fatal("Couldn't load the effect at path " + fileName + ": " + Mix_GetError());

			m_musicCache[fileName] = chunk;
			ret.m_music = chunk;
		}
		// Use the cached version
		else
			ret.m_music = it->second;

		return ret;
	}
}