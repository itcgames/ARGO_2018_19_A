#ifndef _FACTORY_GOAL_H
#define _FACTORY_GOAL_H

#include "../EntityFactory.h"

namespace app::fact
{
	class GoalFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		GoalFactory(math::Vector2f const & position, math::Vector2f const & size);
		~GoalFactory() = default;

		GoalFactory(GoalFactory const &) = default;
		GoalFactory & operator=(GoalFactory const &) = default;

		GoalFactory(GoalFactory &&) = default;
		GoalFactory & operator=(GoalFactory &&) = default;

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
		math::Vector2f const & m_position;
		math::Vector2f const & m_size;
	};
}

#endif // !_FACTORY_GOAL_H
