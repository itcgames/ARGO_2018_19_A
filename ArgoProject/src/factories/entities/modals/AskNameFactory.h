﻿#ifndef _FACTORY_ASK_NAME_H
#define _FACTORY_ASK_NAME_H

#include "../../EntitiesFactory.h"
#include "scenes/SceneType.h"

namespace app::fact::mod
{
	class AskNameFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		AskNameFactory(app::Entity const callingEntity, app::Entity const followEntity, app::sce::SceneType & sceneManagerControl);
		virtual ~AskNameFactory() = default;

		AskNameFactory(AskNameFactory const &) = default;
		AskNameFactory & operator=(AskNameFactory const &) = default;

		AskNameFactory(AskNameFactory &&) = default;
		AskNameFactory & operator=(AskNameFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() final override;
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
		app::Entity const m_callingEntity;
		app::Entity const m_followEntity;
		app::sce::SceneType & m_sceneManagerControl;
	};
}

#endif // !_FACTORY_ASK_NAME_H
