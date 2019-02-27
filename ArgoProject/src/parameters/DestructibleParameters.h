#ifndef _PARAMETERS_DESTRUCTIBLE_H
#define _PARAMETERS_DESTRUCTIBLE_H

namespace app::par
{
	struct DestructibleParameters
	{
	public: // Constructors/Destructor/Assignments
		DestructibleParameters(math::Vector2f const & pos, math::Vector2f const & s, math::Vector2f const & ts, math::Vector2i const & noTiles)
			: position(pos), size(s), tileSize(ts), numberOfTiles(noTiles) {};
		~DestructibleParameters() = default;

		DestructibleParameters(DestructibleParameters const &) = default;
		DestructibleParameters & operator=(DestructibleParameters const &) = default;

		DestructibleParameters(DestructibleParameters &&) = default;
		DestructibleParameters & operator=(DestructibleParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> attachedArea = std::nullopt;
		math::Vector2f const & position;
		math::Vector2f const & size;
		math::Vector2f const & tileSize;
		app::math::Vector2i const & numberOfTiles;
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

#endif // !_PARAMETERS_DESTRUCTIBLE_H
