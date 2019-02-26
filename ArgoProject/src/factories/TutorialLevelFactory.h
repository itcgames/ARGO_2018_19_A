#ifndef _TUTORIAL_FACTORY_LEVEL_H
#define _TUTORIAL_FACTORY_LEVEL_H


#include "EntitiesFactory.h"
#include "deleters/SdlDeleter.h"

namespace app::fact
{
	class TutorialLevelFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		TutorialLevelFactory() = default;
		virtual ~TutorialLevelFactory() = default;

		TutorialLevelFactory(TutorialLevelFactory const &) = default;
		TutorialLevelFactory & operator=(TutorialLevelFactory const &) = default;

		TutorialLevelFactory(TutorialLevelFactory &&) = default;
		TutorialLevelFactory & operator=(TutorialLevelFactory &&) = default;

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

#endif // !_TUTORIAL_FACTORY_LEVEL_H
