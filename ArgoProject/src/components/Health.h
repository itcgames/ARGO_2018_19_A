#ifndef _HEALTH_H
#define _HEALTH_H

namespace app::comp
{
	struct Health
	{
	public: // Constructors/Destructor/Assignments
		Health() = default;
		~Health() = default;

		Health(Health const &) = default;
		Health & operator=(Health const &) = default;

		Health(Health &&) = default;
		Health & operator=(Health &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		int health;
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

#endif // !_HEALTH_H
