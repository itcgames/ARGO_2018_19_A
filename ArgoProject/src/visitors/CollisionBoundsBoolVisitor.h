#ifndef _COLLISION_BOUNDS_BOOL_VISITOR_H
#define _COLLISION_BOUNDS_BOOL_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionBoundsBoolVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionBoundsBoolVisitor(std::variant<cute::c2AABB, cute::c2Circle> const & bounds, bool & collision);
		~CollisionBoundsBoolVisitor() = default;

		CollisionBoundsBoolVisitor(CollisionBoundsBoolVisitor const &) = default;
		CollisionBoundsBoolVisitor & operator=(CollisionBoundsBoolVisitor const &) = default;

		CollisionBoundsBoolVisitor(CollisionBoundsBoolVisitor &&) = default;
		CollisionBoundsBoolVisitor & operator=(CollisionBoundsBoolVisitor &&) = default;

	public: // Public Static Functions
		static bool collisionBetween(std::variant<cute::c2AABB, cute::c2Circle> const & left, std::variant<cute::c2AABB, cute::c2Circle> const & right);
	public: // Public Member Functions
		void operator()(cute::c2AABB const & aabb);
		void operator()(cute::c2Circle const & circle);
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
		std::variant<cute::c2AABB, cute::c2Circle> const & m_leftBounds;
		bool & m_collision;
	};
}

#endif // !_COLLISION_BOUNDS_BOOL_VISITOR_H
