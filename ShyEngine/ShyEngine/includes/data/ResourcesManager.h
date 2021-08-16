#pragma once

// TODO: move audio structures into their own file so that you don't have to include the whole AudioEngine
#include <audio/AudioEngine.h>
#include <data/Texture.h>
#include <data/ImageLoader.h>
#include <data/ResourceCache.h>
#include <SDL2_mixer-2.0.4/SDL_mixer.h>

namespace ShyEngine {

	static Texture loadTexture(const std::string& path)
	{
		Texture ret;
		ret = ImageLoader::loadPNG(path);

		return ret;
	}

	static Music loadMusic(const std::string& path)
	{
		Music ret;
		Mix_Music* chunk = Mix_LoadMUS(path.c_str());
		if (chunk == nullptr)
			Error::fatal("Couldn't load the effect at path " + path + ": " + Mix_GetError());

		ret.setMusic(chunk);

		return ret;
	}

	static SoundEffect loadSoundEffect(const std::string& path)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
		SoundEffect ret;

		if (chunk == nullptr)
			Error::fatal("Couldn't load the effect at path " + path);

		ret.setChunk(chunk);

		return ret;
	}

	class _ResourcesManager
	{
		private:
			ResourceCache<Texture>* m_textureCache = new ResourceCache<Texture>(loadTexture);
			ResourceCache<Music>* m_musicCache = new ResourceCache<Music>(loadMusic);
			ResourceCache<SoundEffect>* m_sfxCache = new ResourceCache<SoundEffect>(loadSoundEffect);

		public:
			_ResourcesManager() {}

			Texture getTexture(const std::string& path);

			Music getMusic(const std::string& path);

			SoundEffect getSoundEffect(const std::string& path);
		
	};

	extern _ResourcesManager ResourcesManager;
}