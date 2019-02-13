#ifndef _COLLISION_UPDATE_VISITOR_H
#define _COLLISION_UPDATE_VISITOR_H

#include "utilities/cute_c2.h"
#include "components/Location.h"
#include "components/Dimensions.h"

namespace app::vis
{
	class CollisionUpdateVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionUpdateVisitor(comp::Location const & location, comp::Dimensions const & dimensions);
		~CollisionUpdateVisitor() = default;

		CollisionUpdateVisitor(CollisionUpdateVisitor const &) = default;
		CollisionUpdateVisitor & operator=(CollisionUpdateVisitor const &) = default;

		CollisionUpdateVisitor(CollisionUpdateVisitor &&) = default;
		CollisionUpdateVisitor & operator=(CollisionUpdateVisitor &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(cute::c2AABB & aabb) const;
		void operator()(cute::c2Circle & circle) const;
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
		comp::Location const & m_location;
		comp::Dimensions const & m_dimensions;
	};
}

#endif // !_COLLISION_TRACKING_VISITOR_H
