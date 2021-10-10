#pragma once

// TODO: move audio structures into their own file so that you don't have to include the whole AudioEngine
#include <audio/AudioEngine.h>
#include <data/Texture.h>
#include <data/ImageLoader.h>
#include <data/ResourceCache.h>
#include <SDL2_mixer-2.0.4/SDL_mixer.h>

namespace ShyEngine {

	/*
		\brief	Loader function (see ResourceCache.h) used to load Textures
		\param path	The path of the texture
		\return The texture identified by the path passed as an argument
	*/
	static Texture loadTexture(const std::string& path)
	{
		Texture ret;
		ret = ImageLoader::loadPNG(path);

		return ret;
	}

	/*
		\brief	Loader function (see ResourceCache.h) used to load Music
		\param path	The path of the audio track
		\return The Music identified by the path passed as an argument
	*/
	static Music loadMusic(const std::string& path)
	{
		Music ret;
		Mix_Music* chunk = Mix_LoadMUS(path.c_str());
		if (chunk == nullptr)
			Error::fatal("Couldn't load the effect at path " + path + ": " + Mix_GetError());

		ret.setMusic(chunk);

		return ret;
	}

	/*
		\brief	Loader function (see ResourceCache.h) used to load SoundEffects
		\param path	The path of the sound effect
		\return The SoundEffect identified by the path passed as an argument
	*/
	static SoundEffect loadSoundEffect(const std::string& path)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
		SoundEffect ret;

		if (chunk == nullptr)
			Error::fatal("Couldn't load the effect at path " + path);

		ret.setChunk(chunk);

		return ret;
	}

	/*
		\brief	The ResourcesManager is a Singleton of type _ResourcesManager used to handle resources such as
			Textures, Musics and SoundEffects

		The ResourcesManager contains a ResourceCache for each resource type in order to optimize memory and loading
		speed. It also exposes methods to load resources without the user noticing any of the underlying
		architecture.
	*/
	class _ResourcesManager
	{
		private:
			ResourceCache<Texture>* m_textureCache = new ResourceCache<Texture>(loadTexture);
			ResourceCache<Music>* m_musicCache = new ResourceCache<Music>(loadMusic);
			ResourceCache<SoundEffect>* m_sfxCache = new ResourceCache<SoundEffect>(loadSoundEffect);

		public:
			_ResourcesManager() {}

			/*
				\brief Returns the texture identified by the path passed as an argument
				\param path The path that identifies the texture to load
				\return The texture identified by the path
			*/
			Texture getTexture(const std::string& path);

			/*
				\brief Returns the Music identified by the path passed as an argument
				\param path The path that identifies the Music to load
				\return The Music identified by the path
			*/
			Music getMusic(const std::string& path);

			/*
				\brief Returns the SoundEffect identified by the path passed as an argument
				\param path The path that identifies the SoundEffect to load
				\return The SoundEffect identified by the path
			*/
			SoundEffect getSoundEffect(const std::string& path);
		
	};

	extern _ResourcesManager ResourcesManager;
}