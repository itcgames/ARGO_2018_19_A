#ifndef _WINDOW_PARAMETERS_H
#define _WINDOW_PARAMETERS_H

namespace app::gra
{
	struct WindowParameters
	{
	public: // Constructors/Destructor/Assignments
		WindowParameters() = default;
		~WindowParameters() = default;

		WindowParameters(WindowParameters const &) = default;
		WindowParameters & operator=(WindowParameters const &) = default;

		WindowParameters(WindowParameters &&) = default;
		WindowParameters & operator=(WindowParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::string title;
		std::size_t width, height;
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

#endif // !_WINDOW_PARAMETERS_H
