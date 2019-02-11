#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "ResourceHandler.h"

namespace app::res
{
	template<bool _Async>
	class ResourceManager
	{
	private: // Private typedefs/enums/usings
		using TextureKey = std::string;
		using TextureHandler = app::res::ResourceHandler<TextureKey, app::gra::Texture, _Async>;
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
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		TextureHandler m_textureHandler;
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
}

#endif // !_RESOURCE_MANAGER_H
