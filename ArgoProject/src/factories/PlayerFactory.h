#ifndef _FACTORY_PLAYER_H
#define _FACTORY_PLAYER_H

#include "EntityFactory.h"
#include "deleters/SdlDeleter.h"
#include "graphics/Texture.h"

namespace app::fact
{
	class PlayerFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		PlayerFactory(app::del::UPtrRenderer const & renderer);
		virtual ~PlayerFactory() = default;

		PlayerFactory(PlayerFactory const &) = default;
		PlayerFactory & operator=(PlayerFactory const &) = default;

		PlayerFactory(PlayerFactory &&) = default;
		PlayerFactory & operator=(PlayerFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::optional<app::Entity> create() override;
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
		std::shared_ptr<app::gra::Texture> m_texture;
	};
}

#endif // !_FACTORY_PLAYER_H
