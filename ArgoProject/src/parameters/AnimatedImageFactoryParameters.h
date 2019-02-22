#ifndef _ANIMATED_IMAGE_FACTORY_PARAMETERS_H
#define _ANIMATED_IMAGE_FACTORY_PARAMETERS_H

#include "resources/TextureKey.h"

namespace app::par
{
	struct AnimatedImageFactoryParameters
	{
	public: // Constructors/Destructor/Assignments
		AnimatedImageFactoryParameters() = default;
		~AnimatedImageFactoryParameters() = default;

		AnimatedImageFactoryParameters(AnimatedImageFactoryParameters const &) = default;
		AnimatedImageFactoryParameters & operator=(AnimatedImageFactoryParameters const &) = default;

		AnimatedImageFactoryParameters(AnimatedImageFactoryParameters &&) = default;
		AnimatedImageFactoryParameters & operator=(AnimatedImageFactoryParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f size;
		math::Vector2f origin;
		math::Vector2f position;
		app::res::TextureKey textureKey;
		math::Vector2f frameSize;
		math::Vector2f frameNumber;
		bool animationLoop = false;
		std::uint32_t zIndex;
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

#endif // !_ANIMATED_IMAGE_FACTORY_PARAMETERS_H
