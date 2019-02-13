#ifndef _DAMAGE_H
#define _DAMAGE_H

namespace app::comp
{
	struct Damage
	{
	public: // Constructors/Destructor/Assignments
		Damage() = default;
		~Damage() = default;

		Damage(Damage const &) = default;
		Damage & operator=(Damage const &) = default;

		Damage(Damage &&) = default;
		Damage & operator=(Damage &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		int damage;
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

#endif // !_DAMAGE_H
