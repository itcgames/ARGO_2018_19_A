#ifndef _COLLISION_CIRCLE_BOOL_VISITOR_H
#define _COLLISION_CIRCLE_BOOL_VISITOR_H

#include "utilities/cute_c2.h"

namespace app::vis
{
	class CollisionCircleBoolVisitor
	{
	public: // Constructors/Destructor/Assignments
		CollisionCircleBoolVisitor(bool & collided, cute::c2Circle const & circle);
		~CollisionCircleBoolVisitor() = default;

		CollisionCircleBoolVisitor(CollisionCircleBoolVisitor const &) = default;
		CollisionCircleBoolVisitor & operator=(CollisionCircleBoolVisitor const &) = default;

		CollisionCircleBoolVisitor(CollisionCircleBoolVisitor &&) = default;
		CollisionCircleBoolVisitor & operator=(CollisionCircleBoolVisitor &&) = default;

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
		cute::c2Circle const & m_circle;
	};
}

#endif // !_COLLISION_CIRCLE_BOOL_VISITOR_H
