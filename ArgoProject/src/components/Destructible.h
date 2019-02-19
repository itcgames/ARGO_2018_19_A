#ifndef _COMPONENTS_DESTRUCTIBLE_H
#define _COMPONENTS_DESTRUCTIBLE_H

namespace app::comp
{
	struct Destructible
	{
	public: // Constructors/Destructor/Assignments
		Destructible() = default;
		~Destructible() = default;

		Destructible(Destructible const &) = default;
		Destructible & operator=(Destructible const &) = default;

		Destructible(Destructible &&) = default;
		Destructible & operator=(Destructible &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> attatchedArea = std::nullopt;
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

#endif // !_COMPONENTS_DESTRUCTIBLE_H
