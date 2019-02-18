#ifndef _COMPONETS_DASHABLE_H
#define _COMPONETS_DASHABLE_H

namespace app::comp
{
	struct Dashable
	{
	public: // Constructors/Destructor/Assignments
		Dashable() = default;
		~Dashable() = default;

		Dashable(Dashable const &) = default;
		Dashable & operator=(Dashable const &) = default;

		Dashable(Dashable &&) = default;
		Dashable & operator=(Dashable &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		bool canDash;
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

#endif // !_COMPONETS_DASHABLE_H
