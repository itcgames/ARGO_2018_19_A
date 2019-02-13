#ifndef _PLAYER_H
#define _PLAYER_H



namespace app::comp
{
	class Player
	{
	public: // Constructors/Destructor/Assignments
		Player() = default;
		~Player() = default;

		Player(Player const &) = default;
		Player & operator=(Player const &) = default;

		Player(Player &&) = default;
		Player & operator=(Player &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		bool falling = false;
		app::Entity currentPlatform;
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

#endif // !_PLAYER_H
