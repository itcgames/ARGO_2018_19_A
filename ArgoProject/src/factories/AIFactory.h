#ifndef _FACTORY_AI_H
#define _FACTORY_AI_H

#include "EntitiesFactory.h"

namespace app::fact
{
	class AIFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		AIFactory(math::Vector2f const & pos, math::Vector2f const & size);
		virtual ~AIFactory() = default;

		AIFactory(AIFactory const &) = default;
		AIFactory & operator=(AIFactory const &) = default;

		AIFactory(AIFactory &&) = default;
		AIFactory & operator=(AIFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() override;
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

#endif // !_FACTORY_AI_H
