#ifndef _COMPONENTS_CURRENTGROUND_H
#define _COMPONENTS_CURRENTGROUND_H

namespace app::comp
{
	struct CurrentGround
	{
	public: // Constructors/Destructor/Assignments
		CurrentGround() = default;
		~CurrentGround() = default;

		CurrentGround(CurrentGround const &) = default;
		CurrentGround & operator=(CurrentGround const &) = default;

		CurrentGround(CurrentGround &&) = default;
		CurrentGround & operator=(CurrentGround &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> currentGround;

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

#endif // !_COMPONENTS_CURRENTGROUND_H
