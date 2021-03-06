﻿#ifndef _FACTORY_LEVEL_DEMO_H
#define _FACTORY_LEVEL_DEMO_H

#include "../EntitiesFactory.h"

namespace app::fact
{
	class LevelDemoFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		LevelDemoFactory(app::Entity camera);
		~LevelDemoFactory() = default;

		LevelDemoFactory(LevelDemoFactory const &) = default;
		LevelDemoFactory & operator=(LevelDemoFactory const &) = default;

		LevelDemoFactory(LevelDemoFactory &&) = default;
		LevelDemoFactory & operator=(LevelDemoFactory &&) = default;

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
		app::Entity m_cameraEntity;
	};
}

#endif // !_FACTORY_LEVEL_DEMO_H
