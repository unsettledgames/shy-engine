#pragma once

#include <SDL2_mixer-2.0.4/SDL_mixer.h>
#include <iostream>
#include <string>
#include <map>
#include <util/IdGenerator.h>

namespace ShyEngine
{
	class SoundEffect
	{
		private:
			friend class AudioEngine;

			Mix_Chunk* m_chunk = nullptr;

			void play(int loops);
			void stop();
			void pause();
			void resume();
		public:
			void setChunk(Mix_Chunk* chunk);
	};

	class Music
	{
		private:
			friend class AudioEngine;

			Mix_Music* m_music = nullptr;

			void play(int loops);
			void stop();
			void pause();
			void resume();
		
		public:
			void setMusic(Mix_Music* music);
	};

	class AudioEngine
	{
		private:
			bool m_initialized = false;

			IdGenerator m_ids;

		public:
			~AudioEngine();

			AudioEngine() {}

			void init();

			void destroy();

			void play(SoundEffect& audio, int loops);
			void pause(SoundEffect& audio);
			void stop(SoundEffect& audio);
			void resume(SoundEffect& audio);

			void play(Music& audio, int loops);
			void pause(Music& audio);
			void stop(Music& audio);
			void resume(Music& audio);
	};
}