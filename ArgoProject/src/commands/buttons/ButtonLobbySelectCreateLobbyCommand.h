﻿#ifndef _BUTTON_LOBBY_SELECT_CREATE_LOBBY_COMMAND_H
#define _BUTTON_LOBBY_SELECT_CREATE_LOBBY_COMMAND_H

#include "BaseMultiplayerCommand.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonLobbySelectCreateLobbyCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonLobbySelectCreateLobbyCommand(std::string const & userName, app::sce::SceneType & sceneControl);
		virtual ~ButtonLobbySelectCreateLobbyCommand() = default;

		ButtonLobbySelectCreateLobbyCommand(ButtonLobbySelectCreateLobbyCommand const &) = default;
		ButtonLobbySelectCreateLobbyCommand & operator=(ButtonLobbySelectCreateLobbyCommand const &) = default;

		ButtonLobbySelectCreateLobbyCommand(ButtonLobbySelectCreateLobbyCommand &&) = default;
		ButtonLobbySelectCreateLobbyCommand & operator=(ButtonLobbySelectCreateLobbyCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() final override;
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
		std::string const m_userName;
		app::sce::SceneType & m_sceneControl;
	};
}

#endif // !_BUTTON_LOBBY_SELECT_CREATE_LOBBY_COMMAND_H
