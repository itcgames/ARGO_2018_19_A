#ifndef _RESOURCE_LOADER_H
#define _RESOURCE_LOADER_H

#include "graphics/Texture.h"
#include "graphics/AudioBuffer.h"
#include "singletons/WindowSingleton.h"

namespace app::res
{
	template<typename _Resource>
	class ResourceLoader
	{
	private: // Private typedefs/enums/usings
	public: // Constructors/Destructor/Assignments
		ResourceLoader() = default;
		~ResourceLoader() = default;

		ResourceLoader(ResourceLoader const &) = default;
		ResourceLoader & operator=(ResourceLoader const &) = default;

		ResourceLoader(ResourceLoader &&) = default;
		ResourceLoader & operator=(ResourceLoader &&) = default;

	public: // Public Static Functions
		static void load(std::shared_ptr<_Resource> & resource, std::string const & file);
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

//
// Full Template class specialization
//

//
// If the bottom gets highlighted as a error
// Code E1449 -> ignore it, it is a known bug in the VS2017 IDE
// https://developercommunity.visualstudio.com/content/problem/258652/variable-template-specialization-gives-error-in-ed.html
//

template<> class app::res::ResourceLoader<app::gra::Texture>
{
private: // Private typedefs/enums/usings
	using Resource = app::gra::Texture;
public: // Constructors/Destructor/Assignments
	ResourceLoader() = default;
	~ResourceLoader() = default;

	ResourceLoader(ResourceLoader const &) = default;
	ResourceLoader & operator=(ResourceLoader const &) = default;

	ResourceLoader(ResourceLoader &&) = default;
	ResourceLoader & operator=(ResourceLoader &&) = default;

public: // Public Static Functions
	static void load(std::shared_ptr<Resource> & resource, std::string const & file)
	{
		auto texture = std::make_shared<Resource>();
		if (texture->load(app::sin::Window::get().getRenderer(), file))
		{
			resource.swap(texture);
		}
		else
		{
			throw std::exception((std::stringstream() << "Failed to load [" << file << "]").str().c_str());
		}
	}
public: // Public Member Functions
public: // Public Static Variables
public: // Public Member Variables
protected: // Protected Static Functions
protected: // Protected Member Functions
protected: // Protected Static Variables
protected: // Protected Member Variables
private: // Private Static Functions
private: // Private Member Functions
private: // Private Static Variables
private: // Private Member Variables
};

template<> class app::res::ResourceLoader<app::gra::Font>
{
private: // Private typedefs/enums/usings
	using Resource = app::gra::Font;
public: // Constructors/Destructor/Assignments
	ResourceLoader() = default;
	~ResourceLoader() = default;

	ResourceLoader(ResourceLoader const &) = default;
	ResourceLoader & operator=(ResourceLoader const &) = default;

	ResourceLoader(ResourceLoader &&) = default;
	ResourceLoader & operator=(ResourceLoader &&) = default;

public: // Public Static Functions
	static void load(std::shared_ptr<Resource> & resource, std::string const & file)
	{
		auto font = std::make_shared<Resource>();
		if (font->load(file))
		{
			resource.swap(font);
		}
		else
		{
			throw std::exception((std::stringstream() << "Failed to load [" << file << "]").str().c_str());
		}
	}
public: // Public Member Functions
public: // Public Static Variables
public: // Public Member Variables
protected: // Protected Static Functions
protected: // Protected Member Functions
protected: // Protected Static Variables
protected: // Protected Member Variables
private: // Private Static Functions
private: // Private Member Functions
private: // Private Static Variables
private: // Private Member Variables
};

template<> class app::res::ResourceLoader<app::gra::AudioBuffer>
{
private: // Private typedefs/enums/usings
	using Resource = app::gra::AudioBuffer;
public: // Constructors/Destructor/Assignments
	ResourceLoader() = default;
	~ResourceLoader() = default;

	ResourceLoader(ResourceLoader const &) = default;
	ResourceLoader & operator=(ResourceLoader const &) = default;

	ResourceLoader(ResourceLoader &&) = default;
	ResourceLoader & operator=(ResourceLoader &&) = default;

public: // Public Static Functions
	static void load(std::shared_ptr<Resource> & resource, std::string const & file)
	{
		auto music = std::make_shared<Resource>();
		if (music->load(file))
		{
			resource.swap(music);
		}
		else
		{
			throw std::exception((std::stringstream() << "Failed to load [" << file << "]").str().c_str());
		}
	}
public: // Public Member Functions
public: // Public Static Variables
public: // Public Member Variables
protected: // Protected Static Functions
protected: // Protected Member Functions
protected: // Protected Static Variables
protected: // Protected Member Variables
private: // Private Static Functions
private: // Private Member Functions
private: // Private Static Variables
private: // Private Member Variables
};

#endif // !_RESOURCE_LOADER_H
