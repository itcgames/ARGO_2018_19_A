#ifndef _COMPONENTS_DOUBLE_JUMP_H
#define _COMPONENTS_DOUBLE_JUMP_H

namespace app::comp
{
	struct DoubleJump
	{
	public: // Constructors/Destructor/Assignments
		DoubleJump() = default;
		~DoubleJump() = default;

		DoubleJump(DoubleJump const &) = default;
		DoubleJump & operator=(DoubleJump const &) = default;

		DoubleJump(DoubleJump &&) = default;
		DoubleJump & operator=(DoubleJump &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		bool canDoubleJump;
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

#endif // !_COMPONENTS_DOUBLE_JUMP_H
