#ifndef _COMPONENT_DIMENSIONS_H
#define _COMPONENT_DIMENSIONS_H

namespace app::comp
{
	struct Dimensions
	{
	public: // Constructors/Destructor/Assignments
		Dimensions() = default;
		~Dimensions() = default;

		Dimensions(Dimensions const &) = default;
		Dimensions(Dimensions &&) = default;

		Dimensions & operator=(Dimensions const &) = default;
		Dimensions & operator=(Dimensions &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f size;
		math::Vector2f origin;
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

#endif // !_COMPONENT_DIMENSIONS_H
