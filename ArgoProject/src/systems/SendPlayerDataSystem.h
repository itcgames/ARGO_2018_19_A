#ifndef _SEND_PLAYER_DATA_SYSTEM_H
#define _SEND_PLAYER_DATA_SYSTEM_H

#include "BaseSystem.h"
#include "network/Client.h"

namespace app::sys
{
	class SendPlayerDataSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		SendPlayerDataSystem();
		virtual ~SendPlayerDataSystem() = default;

		SendPlayerDataSystem(SendPlayerDataSystem const &) = default;
		SendPlayerDataSystem & operator=(SendPlayerDataSystem const &) = default;

		SendPlayerDataSystem(SendPlayerDataSystem &&) = default;
		SendPlayerDataSystem & operator=(SendPlayerDataSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		// Inherited via BaseSystem
		virtual void update(app::time::seconds const & dt) override;
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
		app::net::Client & m_client;
	};
}

#endif // !_SEND_PLAYER_DATA_SYSTEM_H
