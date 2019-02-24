#ifndef _COMP_DISC_H
#define _COMP_DISC_H

namespace app::comp
{
	struct Disc
	{
	public: // Constructors/Destructor/Assignments
		Disc() = default;
		Disc(Disc const &) = default;
		Disc(Disc &&) = default;

		~Disc() = default;

		Disc & operator=(Disc const &) = default;
		Disc & operator=(Disc &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		float discImpulse;
		math::Vector2f offset;
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

#endif // !_COMP_DISC_H
