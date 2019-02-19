#ifndef _FACTORY_NODE_H
#define _FACTORY_NODE_H

#include "EntityFactory.h"
#include "commands/BaseCommand.h"

namespace app::fact
{
	class NodeFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		NodeFactory(math::Vector2f pos, std::list<std::shared_ptr<app::cmnd::BaseCommand>> lcmnds, std::list<std::shared_ptr<app::cmnd::BaseCommand>> icmnds);
		~NodeFactory() = default;

		NodeFactory(NodeFactory const &) = default;
		NodeFactory & operator=(NodeFactory const &) = default;

		NodeFactory(NodeFactory &&) = default;
		NodeFactory & operator=(NodeFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
	public: // Public Static Variables
		constexpr static float s_RADIUS = 10.0f;
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		math::Vector2f m_position;
		std::list<std::shared_ptr<app::cmnd::BaseCommand>> m_loopCommands;
		std::list<std::shared_ptr<app::cmnd::BaseCommand>> m_initialCommands;
	};
}

#endif // !_FACTORY_NODE_H
