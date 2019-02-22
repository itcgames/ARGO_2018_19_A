#ifndef _PARAMETERS_DESTRUCTIBLE_H
#define _PARAMETERS_DESTRUCTIBLE_H

namespace app::par
{
	struct DestructibleParameters
	{
	public: // Constructors/Destructor/Assignments
		DestructibleParameters(math::Vector2f const & pos, math::Vector2f const & s) : position(pos), size(s) {};
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
