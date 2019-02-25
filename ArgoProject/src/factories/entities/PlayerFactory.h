#ifndef _FACTORY_PLAYER_H
#define _FACTORY_PLAYER_H

#include "../EntityFactory.h"

namespace app::fact
{
	class PlayerFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		PlayerFactory();
		virtual ~PlayerFactory() = default;

		PlayerFactory(PlayerFactory const &) = default;
		PlayerFactory & operator=(PlayerFactory const &) = default;

		PlayerFactory(PlayerFactory &&) = default;
		PlayerFactory & operator=(PlayerFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
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

#endif // !_FACTORY_PLAYER_H
