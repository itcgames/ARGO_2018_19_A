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
		using FontHandler = app::res::ResourceHandler<FontKey, int, _Async>; // change `int` when font loading is created
		using AudioHandler = app::res::ResourceHandler<AudioKey, int, _Async>; // change `int` when audio loading is created
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

		std::shared_ptr<int> getFont(FontKey const & key);
		void loadFont(FontKey const & key, std::string const & file);

		std::shared_ptr<int> getAudio(AudioKey const & key);
		void loadAudio(AudioKey const & key, std::string const & file);
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		TextureHandler m_textureHandler;
		FontHandler m_fontHandler;
		AudioHandler m_audioHandler;
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
	std::shared_ptr<int> ResourceManager<_Async>::getFont(FontKey const & key)
	{
		return m_fontHandler.get(key);
	}

	template<bool _Async>
	void ResourceManager<_Async>::loadFont(FontKey const & key, std::string const & file)
	{
		m_fontHandler.load(key, file);
	}

	template<bool _Async>
	std::shared_ptr<int> ResourceManager<_Async>::getAudio(AudioKey const & key)
	{
		return m_audioHandler.get(key);
	}

	template<bool _Async>
	void ResourceManager<_Async>::loadAudio(AudioKey const & key, std::string const & file)
	{
		m_audioHandler.load(key, file);
	}
}

#endif // !_RESOURCE_MANAGER_H
