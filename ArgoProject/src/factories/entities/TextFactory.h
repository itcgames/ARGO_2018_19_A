#ifndef _TEXT_FACTORY_H
#define _TEXT_FACTORY_H

#include "factories/EntityFactory.h"

namespace app::fact
{
	class TextFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		TextFactory(math::Vector2f const & position, math::Vector2f const & size, std::string const & text);
		virtual ~TextFactory() = default;

		TextFactory(TextFactory const &) = default;
		TextFactory & operator=(TextFactory const &) = default;

		TextFactory(TextFactory &&) = default;
		TextFactory & operator=(TextFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
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
		std::string const & m_text;
	};
}

#endif // !_TEXT_FACTORY_H
