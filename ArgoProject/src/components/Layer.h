#ifndef _COMP_LAYER_H
#define _COMP_LAYER_H

namespace app::comp
{
	struct Layer
	{
	public: // Constructors/Destructor/Assignments
		Layer() = default;
		~Layer() = default;

		Layer(Layer const &) = default;
		Layer & operator=(Layer const &) = default;

		Layer(Layer &&) = default;
		Layer & operator=(Layer &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::uint32_t zIndex = 100u;
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

#endif // !_COMP_LAYER_H
