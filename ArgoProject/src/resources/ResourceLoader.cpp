#include "stdafx.h"
#include "ResourceLoader.h"

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
	static void load(std::shared_ptr<Resource> resource, std::string const & file)
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
