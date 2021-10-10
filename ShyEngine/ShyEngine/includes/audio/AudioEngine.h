#pragma once

#include <SDL2_mixer-2.0.4/SDL_mixer.h>
#include <iostream>
#include <string>
#include <map>
#include <util/IdGenerator.h>

namespace ShyEngine
{
	/*
		\brief Represents a sound effect and the methods to handle its reproduction

		Mostly a wrapper around the Mix_Chunk type defined in SDL_Mixer
	*/
	class SoundEffect
	{
		private:
			friend class AudioEngine;

			// Container for the sound effect
			Mix_Chunk* m_chunk = nullptr;

			/*
				\brief	Plays a sound effect.
				
				\param	loops: number of times the effect should be played
			*/
			void play(int loops);

			/*
				\brief	Stops a sound effect
			*/
			void stop();

			/*
				\brief	Pauses a sound effect that can be resumed with resumed()
			*/
			void pause();

			/*
				\brief	Resumes the reproduction of a paused sound effect
			*/
			void resume();
		
		public:
			/*
				\brief	Sets the chunk to be played

				\param chunk:	The chunk to be played
			*/
			void setChunk(Mix_Chunk* chunk);
	};

	/*
		\brief Represents music and the methods to handle its reproduction

		Mostly a wrapper around the Mix_Music type defined in SDL_Mixer
	*/
	class Music
	{
		private:
			friend class AudioEngine;

			// Container for the music to be reproduced
			Mix_Music* m_music = nullptr;

			/*
				\brief	Plays a music
				\param	loops: number of times the music should be played
			*/
			void play(int loops);

			/*
				\brief	Stops a music
			*/
			void stop();

			/*
				\brief	Pauses a music that can be resumed with resumed()
			*/
			void pause();

			/*
				\brief	Resumes the reproduction of a paused music
			*/
			void resume();
		
		public:
			/*
				\brief	Sets the chunk to be played
				\param chunk:	The chunk to be played
			*/
			void setMusic(Mix_Music* music);
	};

	/*
		\brief The AudioEngine is the class used to handle the reproduction of audio files.

		It contains methods to play, pause, resume and stop sound effects or full audio tracks.
	*/
	class AudioEngine
	{
		private:
			// Has the AudioEngine been initialized?
			bool m_initialized = false;
			// Used to generate the ids of the sound effects
			IdGenerator m_ids;

		public:
			~AudioEngine();

			AudioEngine() {}

			/*
				\brief Initializes the AudioEngine

				It tells SDL_Mixer which audio types are supported (OGG, MP3, WAV etc) and sets the m_initialized
				flag accordingly.
			*/
			void init();

			/*
				\brief Releases all the resources held by the AudioEngine
			*/
			void destroy();

			/* These functions are just wrappers around the SoundEffect and Music methods */

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