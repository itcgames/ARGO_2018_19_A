#ifndef _COLLISION_BOUNDS_MANIFEST_VISITOR_H
#define _COLLISION_BOUNDS_MANIFEST_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionBoundsManiVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionBoundsManiVisitor(std::variant<cute::c2AABB, cute::c2Circle> const & bounds, cute::c2Manifold & manifold);
		~CollisionBoundsManiVisitor() = default;

		CollisionBoundsManiVisitor(CollisionBoundsManiVisitor const &) = default;
		CollisionBoundsManiVisitor & operator=(CollisionBoundsManiVisitor const &) = default;

		CollisionBoundsManiVisitor(CollisionBoundsManiVisitor &&) = default;
		CollisionBoundsManiVisitor & operator=(CollisionBoundsManiVisitor &&) = default;

	public: // Public Static Functions
		static cute::c2Manifold collisionBetween(std::variant<cute::c2AABB, cute::c2Circle> const & left, std::variant<cute::c2AABB, cute::c2Circle> const & right);
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
		std::variant<cute::c2AABB, cute::c2Circle> const & m_bounds;
		cute::c2Manifold & m_manifold;
	};
}

#endif // !_COLLISION_BOUNDS_MANIFEST_VISITOR_H
