#ifndef _COMPONENT_LOCATION_H
#define _COMPONENT_LOCATION_H

namespace app::comp
{
	struct Location
	{
	public: // Constructors/Destructor/Assignments
		Location() = default;
		~Location() = default;

		Location(Location const &) = default;
		Location(Location &&) = default;

		Location & operator=(Location const &) = default;
		Location & operator=(Location &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f position;
		float orientation = 0.0f;
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

#endif // !_COMPONENT_LOCATION_H
