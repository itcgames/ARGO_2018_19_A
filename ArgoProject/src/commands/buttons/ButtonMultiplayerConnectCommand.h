#ifndef _BUTTON_MULTIPLAYER_CONNECT_COMMAND_H
#define _BUTTON_MULTIPLAYER_CONNECT_COMMAND_H

#include "ButtonMultiplayerCommand.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonMultiplayerConnectCommand : public ButtonMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMultiplayerConnectCommand(std::string && serverIp, std::int32_t serverPort, app::sce::SceneType & sceneManagerControl);
		virtual ~ButtonMultiplayerConnectCommand() = default;

		ButtonMultiplayerConnectCommand(ButtonMultiplayerConnectCommand const &) = default;
		ButtonMultiplayerConnectCommand & operator=(ButtonMultiplayerConnectCommand const &) = default;

		ButtonMultiplayerConnectCommand(ButtonMultiplayerConnectCommand &&) = default;
		ButtonMultiplayerConnectCommand & operator=(ButtonMultiplayerConnectCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		std::string const m_serverIp;
		std::int32_t const m_serverPort;
		app::sce::SceneType & m_sceneManagerControl;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_MULTIPLAYER_CONNECT_COMMAND_H
