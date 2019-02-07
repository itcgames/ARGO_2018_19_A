#ifndef _COMPONENT_DASH_H
#define _COMPONENT_DASH_H

namespace app::comp
{
	struct Dash
	{
	public: // Constructors/Destructor/Assignments
		Dash() = default;
		~Dash() = default;

		Dash(Dash const &) = default;
		Dash & operator=(Dash const &) = default;

		Dash(Dash &&) = default;
		Dash & operator=(Dash &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		float speed;
		float direction;
		float drag;
		float dragCutoff;
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

#endif // !_COMPONENT_DASH_H
