#ifndef _COLLISION_AABB_MANIFEST_VISITOR_H
#define _COLLISION_AABB_MANIFEST_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionAabbManiVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionAabbManiVisitor(cute::c2Manifold & manifold, cute::c2AABB const & aabb);
		~CollisionAabbManiVisitor() = default;

		CollisionAabbManiVisitor(CollisionAabbManiVisitor const &) = default;
		CollisionAabbManiVisitor & operator=(CollisionAabbManiVisitor const &) = default;

		CollisionAabbManiVisitor(CollisionAabbManiVisitor &&) = default;
		CollisionAabbManiVisitor & operator=(CollisionAabbManiVisitor &&) = default;

	public: // Public Static Functions
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
		cute::c2Manifold & m_manifold;
		cute::c2AABB const & m_aabb;
	};
}

#endif // !_COLLISION_AABB_MANIFEST_VISITOR_H
