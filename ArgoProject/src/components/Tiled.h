#ifndef _COMPONENTS_TILED_H
#define _COMPONENTS_TILED_H

namespace app::comp
{
	struct Tiled
	{
	public: // Constructors/Destructor/Assignments
		Tiled() = default;
		~Tiled() = default;

		Tiled(Tiled const &) = default;
		Tiled & operator=(Tiled const &) = default;

		Tiled(Tiled &&) = default;
		Tiled & operator=(Tiled &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::vector<app::Entity> tiles;
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

#endif // !_COMPONENTS_TILED_H
