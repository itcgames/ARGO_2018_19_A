#ifndef _BOMB_COMP_H
#define _BOMB_COMP_H

namespace app::comp
{
	struct Bomb
	{
	public: // Constructors/Destructor/Assignments
		Bomb() = default;
		~Bomb() = default;

		Bomb(Bomb const &) = default;
		Bomb & operator=(Bomb const &) = default;

		Bomb(Bomb &&) = default;
		Bomb & operator=(Bomb &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		float impulse;
		bool exploded;
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

#endif // !_BOMB_COMP_H
