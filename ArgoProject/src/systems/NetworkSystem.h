#ifndef _NETWORK_SYSTEM_H
#define _NETWORK_SYSTEM_H

#include "BaseSystem.h"
#include "network/Client.h"

namespace app::sys
{
	class NetworkSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		NetworkSystem();
		virtual ~NetworkSystem() = default;

		NetworkSystem(NetworkSystem const &) = default;
		NetworkSystem & operator=(NetworkSystem const &) = default;

		NetworkSystem(NetworkSystem &&) = default;
		NetworkSystem & operator=(NetworkSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		void output(std::string const & msg) const;
		void output(std::initializer_list<std::string> const & msgs) const;
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		app::net::Client & m_client;
		app::net::PacketType m_packetType;
	};
}

#endif // !_NETWORK_SYSTEM_H
