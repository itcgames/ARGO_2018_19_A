#ifndef _COMPONENT_GHOST_H
#define _COMPONENT_GHOST_H

namespace app::comp
{
	struct Ghost
	{
	public: // Constructors/Destructor/Assignments
		Ghost() = default;
		~Ghost() = default;

		Ghost(Ghost const &) = default;
		Ghost & operator=(Ghost const &) = default;

		Ghost(Ghost &&) noexcept = default;
		Ghost & operator=(Ghost &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		int id;
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

#endif // !_COMPONENT_GHOST_H
