#include <audio/AudioEngine.h>
#include <util/Error.h>

namespace ShyEngine
{
	/*******************************************MUSIC***********************************************************/
	// The functions in the AudioEngine that are not commented are just wrappers around the ones defined in
	// SDL_Mixers
	void Music::play(int loops /* = 1 */)
	{
		if (Mix_PlayMusic(m_music, loops) < 0)
			Error::fatal("Couldn't play music");
	}

	void Music::setMusic(Mix_Music* music)
	{
		m_music = music;
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

	/*******************************************SOUND EFFECTS***********************************************************/

	void SoundEffect::play(int loops /* = 0 */)
	{
		// IMPROVEMENT: -1 is the number of channels, could be nice to have some smart way to
		// select the right channel. Find a way to detect paused channels or something, in general have a 
		// look at how channels work
		if (Mix_PlayChannel(-1, m_chunk, loops) < 0)
			if (Mix_PlayChannel(0, m_chunk, loops) < 0)
				Error::fatal("Couldn't play sound effect");
	}

	void SoundEffect::setChunk(Mix_Chunk* chunk)
	{
		m_chunk = chunk;
	}

	void SoundEffect::pause()
	{
		Mix_PauseMusic();
	}

	void SoundEffect::stop()
	{
		Mix_HaltMusic();
	}

	void SoundEffect::resume()
	{
		Mix_ResumeMusic();
	}

	/*******************************************AUDIO ENGINE***********************************************************/

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
			std::cout << "WARNING: tried to initialize the AudioEngine twice" << std::endl;
	}

	void AudioEngine::destroy()
	{
		if (m_initialized)
		{
			m_initialized = false;

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	void AudioEngine::play(SoundEffect& toPlay, int loops)
	{
		toPlay.play(loops);
	}

	void AudioEngine::resume(SoundEffect& audio)
	{
		audio.resume();
	}

	void AudioEngine::pause(SoundEffect& audio)
	{
		audio.pause();
	}

	void AudioEngine::stop(SoundEffect& audio)
	{
		audio.stop();
	}

	void AudioEngine::play(Music& toPlay, int loops)
	{
		toPlay.play(loops);
	}

	void AudioEngine::resume(Music& audio)
	{
		audio.resume();
	}

	void AudioEngine::pause(Music& audio)
	{
		audio.pause();
	}

	void AudioEngine::stop(Music& audio)
	{
		audio.stop();
	}
}