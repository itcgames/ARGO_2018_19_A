#ifndef _FACTORY_LEVEL_H
#define _FACTORY_LEVEL_H


#include "EntitiesFactory.h"
#include "deleters/SdlDeleter.h"

namespace app::fact
{
	class LevelFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		LevelFactory() = default;
		virtual ~LevelFactory() = default;

		LevelFactory(LevelFactory const &) = default;
		LevelFactory & operator=(LevelFactory const &) = default;

		LevelFactory(LevelFactory &&) = default;
		LevelFactory & operator=(LevelFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() override;
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

#endif // !_FACTORY_LEVEL_H
