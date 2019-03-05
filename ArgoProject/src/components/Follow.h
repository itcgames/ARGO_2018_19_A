﻿#ifndef _COMP_FOLLOW_ENTITY_H
#define _COMP_FOLLOW_ENTITY_H

namespace app::comp
{
	struct Follow
	{
	public: // Constructors/Destructor/Assignments
		Follow() = default;
		Follow(Follow const &) = default;
		Follow(Follow &&) = default;

		~Follow() = default;

		Follow & operator=(Follow const &) = default;
		Follow & operator=(Follow &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		app::Entity entity;
		math::Vector2f offset = { 0.0f, 0.0f };
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_COMP_FOLLOW_ENTITY_H
