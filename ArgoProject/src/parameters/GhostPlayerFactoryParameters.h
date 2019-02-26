#ifndef _GHOST_PLAYER_FACTORY_PARAMETERS_H
#define _GHOST_PLAYER_FACTORY_PARAMETERS_H

namespace app::par
{
	struct GhostPlayerFactoryParameters
	{
	public: // Constructors/Destructor/Assignments
		GhostPlayerFactoryParameters() = default;
		~GhostPlayerFactoryParameters() = default;

		GhostPlayerFactoryParameters(GhostPlayerFactoryParameters const &) = default;
		GhostPlayerFactoryParameters & operator=(GhostPlayerFactoryParameters const &) = default;

		GhostPlayerFactoryParameters(GhostPlayerFactoryParameters &&) = default;
		GhostPlayerFactoryParameters & operator=(GhostPlayerFactoryParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f position;
		int id;
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

#endif // !_GHOST_PLAYER_FACTORY_PARAMETERS_H
