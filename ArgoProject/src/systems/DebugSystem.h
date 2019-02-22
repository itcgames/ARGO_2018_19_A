#ifndef _DEBUG_SYSTEM_H
#define _DEBUG_SYSTEM_H

#include "BaseSystem.h"
#include "network/Client.h"
#include "scenes/SceneType.h"


namespace app::sys
{
	class DebugSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		DebugSystem(app::sce::SceneType& _targetScene);
		virtual ~DebugSystem() = default;

		DebugSystem(DebugSystem const &) = default;
		DebugSystem & operator=(DebugSystem const &) = default;

		DebugSystem(DebugSystem &&) = default;
		DebugSystem & operator=(DebugSystem &&) = default;


	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		void serverTesting();
		void sceneSwapping();
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		app::inp::KeyHandler & m_keyHandler;
		app::net::Client& m_client;
		bool m_updateVariable = false;
		bool m_connected;
		app::sce::SceneType& m_targetScene;

	};
}

#endif // !_DEBUG_SYSTEM_H
