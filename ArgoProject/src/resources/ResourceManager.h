#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "ResourceHandler.h"
#include "TextureKey.h"
#include "FontKey.h"
#include "AudioKey.h"

namespace app::res
{
	template<bool _Async>
	class ResourceManager
	{
	private: // Private typedefs/enums/usings
		using TextureHandler = app::res::ResourceHandler<TextureKey, app::gra::Texture, _Async>;
		using FontHandler = app::res::ResourceHandler<FontKey, app::gra::Font, _Async>; // change `int` when font loading is created
		using AudioHandlerMusic = app::res::ResourceHandler<AudioKey, app::gra::AudioBufferMusic, _Async>; // change `int` when audio loading is created
		using AudioHandlerSFX = app::res::ResourceHandler<AudioKey, app::gra::AudioBufferSFX, _Async>;
	public: // Constructors/Destructor/Assignments
		ResourceManager() = default;
		~ResourceManager() = default;

		ResourceManager(ResourceManager const &) = default;
		ResourceManager & operator=(ResourceManager const &) = default;

		ResourceManager(ResourceManager &&) = default;
		ResourceManager & operator=(ResourceManager &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		std::shared_ptr<app::gra::Texture> getTexture(TextureKey const & key);
		void loadTexture(TextureKey const & key, std::string const & file);

		std::shared_ptr<app::gra::Font> getFont(FontKey const & key);
		void loadFont(FontKey const & key, std::string const & file);

		std::shared_ptr<app::gra::AudioBufferMusic> getAudioM(AudioKey const & key);
		void loadAudioMusic(AudioKey const & key, std::string const & file);

		std::shared_ptr<app::gra::AudioBufferSFX> getAudioS(AudioKey const & key);
		void loadAudioSFX(AudioKey const & key, std::string const & file);

		bool isLoaded();
		bool isTextureLoaded();
		bool isFontLoaded();
		bool isMusicAudioLoaded();
		bool isSFXAudioLoaded();
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		TextureHandler m_textureHandler;
		FontHandler m_fontHandler;
		AudioHandlerMusic m_audioMusicHandler;
		AudioHandlerSFX m_audioSFXHandler;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};

	template<bool _Async>
	std::shared_ptr<app::gra::Texture> ResourceManager<_Async>::getTexture(TextureKey const & key)
	{
		return m_textureHandler.get(key);
	}

	template<bool _Async>
	void ResourceManager<_Async>::loadTexture(TextureKey const & key, std::string const & file)
	{
		m_textureHandler.load(key, file);
	}

	template<bool _Async>
	std::shared_ptr<app::gra::Font> ResourceManager<_Async>::getFont(FontKey const & key)
	{
		return m_fontHandler.get(key);
	}

	template<bool _Async>
	void ResourceManager<_Async>::loadFont(FontKey const & key, std::string const & file)
	{
		m_fontHandler.load(key, file);
	}

	template<bool _Async>
	std::shared_ptr<app::gra::AudioBufferMusic> ResourceManager<_Async>::getAudioM(AudioKey const & key)
	{
		return m_audioMusicHandler.get(key);
	}

	template<bool _Async>
	std::shared_ptr<app::gra::AudioBufferSFX> ResourceManager<_Async>::getAudioS(AudioKey const & key)
	{
		return m_audioSFXHandler.get(key);
	}

	template<bool _Async>
	void ResourceManager<_Async>::loadAudioMusic(AudioKey const & key, std::string const & file)
	{
		m_audioMusicHandler.load(key, file);
	}

	template<bool _Async>
	void ResourceManager<_Async>::loadAudioSFX(AudioKey const & key, std::string const & file)
	{
		m_audioSFXHandler.load(key, file);
	}

	template<bool _Async>
	bool ResourceManager<_Async>::isLoaded()
	{
		return this->isTextureLoaded() && this->isFontLoaded() && this->isMusicAudioLoaded() && this->isSFXAudioLoaded();
	}
	template<bool _Async>
	bool ResourceManager<_Async>::isTextureLoaded()
	{
		return m_textureHandler.isAllLoaded();
	}

	template<bool _Async>
	bool ResourceManager<_Async>::isFontLoaded()
	{
		return m_fontHandler.isAllLoaded();
	}

	template<bool _Async>
	bool ResourceManager<_Async>::isMusicAudioLoaded()
	{
		return m_audioMusicHandler.isAllLoaded();
	}

	template<bool _Async>
	bool ResourceManager<_Async>::isSFXAudioLoaded()
	{
		return  m_audioSFXHandler.isAllLoaded();
	}
}

#endif // !_RESOURCE_MANAGER_H
