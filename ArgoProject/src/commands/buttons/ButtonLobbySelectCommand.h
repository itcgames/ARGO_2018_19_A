#ifndef _BUTTON_LOBBY_SELECT_COMMAND_H
#define _BUTTON_LOBBY_SELECT_COMMAND_H

#include "BaseMultiplayerCommand.h"
#include "shared/network/Lobby.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonLobbySelectCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonLobbySelectCommand(app::net::Lobby const lobby, app::sce::SceneType & sceneControl);
		virtual ~ButtonLobbySelectCommand() = default;

		ButtonLobbySelectCommand(ButtonLobbySelectCommand const &) = default;
		ButtonLobbySelectCommand & operator=(ButtonLobbySelectCommand const &) = default;

		ButtonLobbySelectCommand(ButtonLobbySelectCommand &&) = default;
		ButtonLobbySelectCommand & operator=(ButtonLobbySelectCommand &&) = default;

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
		std::string const & getPlayerName(std::int32_t const & index) const;
	private: // Private Static Variables
	private: // Private Member Variables
		app::net::Lobby const m_lobby;
		app::sce::SceneType & m_sceneControl;
	};
}

#endif // !_BUTTON_LOBBY_SELECT_COMMAND_H
