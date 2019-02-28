#ifndef _IMAGE_FACTORY_H
#define _IMAGE_FACTORY_H

#include "../EntityFactory.h"

namespace app::fact
{
	class ImageFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		ImageFactory(
			  math::Vector2f const & position
			, math::Vector2f const & size
			, math::Vector2f const & origin
			, app::res::TextureKey const & textureKey
			, std::uint32_t const & zIndex
			, std::optional<app::Entity> const & follow = std::nullopt);
		virtual ~ImageFactory() = default;

		ImageFactory(ImageFactory const &) = default;
		ImageFactory & operator=(ImageFactory const &) = default;

		ImageFactory(ImageFactory &&) = default;
		ImageFactory & operator=(ImageFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		math::Vector2f const & m_position;
		math::Vector2f const & m_size;
		math::Vector2f const & m_origin;
		app::res::TextureKey const & m_textureKey;
		std::uint32_t const & m_zIndex;
		std::optional<app::Entity> const m_follow;
	};
}

#endif // !_IMAGE_FACTORY_H
