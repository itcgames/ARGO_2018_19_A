#ifndef _BACKGROUND_IMAGE_FACTORY_H
#define _BACKGROUND_IMAGE_FACTORY_H

#include "../EntityFactory.h"

namespace app::fact
{
	class BackgroundImageFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		BackgroundImageFactory() = default;
		virtual ~BackgroundImageFactory() = default;

		BackgroundImageFactory(BackgroundImageFactory const &) = default;
		BackgroundImageFactory & operator=(BackgroundImageFactory const &) = default;

		BackgroundImageFactory(BackgroundImageFactory &&) = default;
		BackgroundImageFactory & operator=(BackgroundImageFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() final override;
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

#endif // !_BACKGROUND_IMAGE_FACTORY_H
