#ifndef _COMP_FACING_H
#define _COMP_FACING_H

namespace app::comp
{
	struct Facing
	{
	public: // Constructors/Destructor/Assignments
		Facing() = default;
		~Facing() = default;

		Facing(Facing const &) = default;
		Facing & operator=(Facing const &) = default;

		Facing(Facing &&) = default;
		Facing & operator=(Facing &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		bool isRight;
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

#endif // !_COMP_FACING_H
