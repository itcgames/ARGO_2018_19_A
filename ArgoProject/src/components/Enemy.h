#ifndef _COMPONENT_ENEMY_H
#define _COMPONENT_ENEMY_H

namespace app::comp
{
	struct Enemy
	{
	public: // Constructors/Destructor/Assignments
		Enemy() = default;
		~Enemy() = default;

		Enemy(Enemy const &) = default;
		Enemy(Enemy &&) = default;

		Enemy & operator=(Enemy const &) = default;
		Enemy & operator=(Enemy &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
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
	};
}

#endif // !_COMPONENT_DIMENSIONS_H
