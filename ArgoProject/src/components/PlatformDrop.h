#ifndef _COMPONENTS_PLATFORM_DROP_H
#define _COMPONENTS_PLATFORM_DROP_H



namespace app::comp
{
	class PlatformDrop
	{
	public: // Constructors/Destructor/Assignments
		PlatformDrop() = default;
		~PlatformDrop() = default;

		PlatformDrop(PlatformDrop const &) = default;
		PlatformDrop & operator=(PlatformDrop const &) = default;

		PlatformDrop(PlatformDrop &&) = default;
		PlatformDrop & operator=(PlatformDrop &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		bool falling = false;
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

#endif // !_COMPONENTS_PLATFORM_DROP_H
