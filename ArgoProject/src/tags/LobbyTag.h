#ifndef _LOBBY_TAG_H
#define _LOBBY_TAG_H

namespace app::tag
{
	struct Lobby
	{
	public: // Constructors/Destructor/Assignments
		Lobby() = default;
		~Lobby() = default;

		Lobby(Lobby const &) = default;
		Lobby & operator=(Lobby const &) = default;

		Lobby(Lobby &&) = default;
		Lobby & operator=(Lobby &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::string name;
		bool isHost = false;
		std::array<std::optional<std::string>, 4> players;
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

#endif // !_LOBBY_TAG_H
