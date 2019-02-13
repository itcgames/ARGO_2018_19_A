#ifndef _COLLISION_AABB_TO_AABB_BOOL_VISITOR_H
#define _COLLISION_AABB_TO_AABB_BOOL_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionAabbBoolVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionAabbBoolVisitor(bool & collided, cute::c2AABB const & leftAabb);
		~CollisionAabbBoolVisitor() = default;

		CollisionAabbBoolVisitor(CollisionAabbBoolVisitor const &) = default;
		CollisionAabbBoolVisitor & operator=(CollisionAabbBoolVisitor const &) = default;

		CollisionAabbBoolVisitor(CollisionAabbBoolVisitor &&) = default;
		CollisionAabbBoolVisitor & operator=(CollisionAabbBoolVisitor &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(cute::c2AABB const & aabb);
		void operator()(cute::c2Circle const & circle);
		void operator()(cute::c2Ray const & ray);
		void operator()(cute::c2Capsule const & capsule);
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
		bool & m_result;
		cute::c2AABB const & m_left;
	};
}

#endif // !_COLLISION_AABB_TO_AABB_BOOL_VISITOR_H
