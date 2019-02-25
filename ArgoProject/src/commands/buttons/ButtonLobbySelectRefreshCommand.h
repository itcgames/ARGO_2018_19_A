#ifndef _BUTTON_LOBBY_SELECT_REFRESH_COMMAND_H
#define _BUTTON_LOBBY_SELECT_REFRESH_COMMAND_H

#include "BaseMultiplayerCommand.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonLobbySelectRefreshCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonLobbySelectRefreshCommand(std::forward_list<app::Entity> entities, app::sce::SceneType & sceneControl);
		virtual ~ButtonLobbySelectRefreshCommand() = default;

		ButtonLobbySelectRefreshCommand(ButtonLobbySelectRefreshCommand const &) = default;
		ButtonLobbySelectRefreshCommand & operator=(ButtonLobbySelectRefreshCommand const &) = default;

		ButtonLobbySelectRefreshCommand(ButtonLobbySelectRefreshCommand &&) = default;
		ButtonLobbySelectRefreshCommand & operator=(ButtonLobbySelectRefreshCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		std::forward_list<app::Entity> m_entities;
		app::sce::SceneType & m_sceneControl;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_LOBBY_SELECT_REFRESH_COMMAND_H
