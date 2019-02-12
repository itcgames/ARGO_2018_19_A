#ifndef _COLLISION_CIRCLE_MANIFEST_VISITOR_H
#define _COLLISION_CIRCLE_MANIFEST_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionCircleManiVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionCircleManiVisitor(cute::c2Manifold & manifold, cute::c2Circle const & circle);
		~CollisionCircleManiVisitor() = default;

		CollisionCircleManiVisitor(CollisionCircleManiVisitor const &) = default;
		CollisionCircleManiVisitor & operator=(CollisionCircleManiVisitor const &) = default;

		CollisionCircleManiVisitor(CollisionCircleManiVisitor &&) = default;
		CollisionCircleManiVisitor & operator=(CollisionCircleManiVisitor &&) = default;

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
		cute::c2Circle const & m_circle;
	};
}

#endif // !_COLLISION_CIRCLE_MANIFEST_VISITOR_H
