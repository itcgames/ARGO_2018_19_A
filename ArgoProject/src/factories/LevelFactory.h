#ifndef _FACTORY_LEVEL_H
#define _FACTORY_LEVEL_H


#include "EntityFactory.h"
#include "deleters/SdlDeleter.h"

namespace app::fact
{
	class LevelFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		LevelFactory(app::del::UPtrRenderer const & renderer);
		virtual ~LevelFactory() = default;

		LevelFactory(LevelFactory const &) = default;
		LevelFactory & operator=(LevelFactory const &) = default;

		LevelFactory(LevelFactory &&) = default;
		LevelFactory & operator=(LevelFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::optional<app::Entity> create() override;
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
