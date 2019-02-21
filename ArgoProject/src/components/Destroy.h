#ifndef _COMP_DESTROY_H
#define _COMP_DESTROY_H

namespace app::comp
{
	struct Destroy
	{
	public: // Constructors/Destructor/Assignments
		Destroy() = default;
		~Destroy() = default;

		Destroy(Destroy const &) = default;
		Destroy & operator=(Destroy const &) = default;

		Destroy(Destroy &&) = default;
		Destroy & operator=(Destroy &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
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

#endif // !_COMP_DESTROY_H
