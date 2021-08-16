#pragma once

#include <SDL2_mixer-2.0.4/SDL_mixer.h>
#include <iostream>
#include <string>
#include <map>

// IMPROVEMENT: pause, stop, resume

namespace ShyEngine
{
	// REFACTOR: put these in separate files, use a hierarchy and expand them
	class SoundEffect 
	{
		private:
			friend class AudioEngine;

			Mix_Chunk* m_chunk = nullptr;
		public:
			void play(int loops = 0);

			void setChunk(Mix_Chunk* chunk);
	};

	class Music
	{
		private:
			friend class AudioEngine;

			Mix_Music* m_music = nullptr;
		public:
			void play(int loops = -1);

			static void stop();

			static void pause();

			static void resume();

			void setMusic(Mix_Music* music);
	};

	class AudioEngine
	{
		private:
			bool m_initialized = false;

			std::map<std::string, Mix_Chunk*> m_effectsCache;

			std::map<std::string, Mix_Music*> m_musicCache;

		public:
			~AudioEngine();

			AudioEngine() {}

			void init();

			void destroy();

	};
}