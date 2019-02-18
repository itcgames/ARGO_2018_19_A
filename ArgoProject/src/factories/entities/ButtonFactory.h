#ifndef _BUTTON_FACTORY_H
#define _BUTTON_FACTORY_H

#include "../EntityFactory.h"
#include "parameters/ButtonFactoryParameters.h"

namespace app::fact
{
	class ButtonFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		ButtonFactory(par::ButtonFactoryParameters const & params) noexcept;
		virtual ~ButtonFactory() noexcept = default;

		ButtonFactory(ButtonFactory const &) noexcept = default;
		ButtonFactory & operator=(ButtonFactory const &) noexcept = default;

		ButtonFactory(ButtonFactory &&) noexcept = default;
		ButtonFactory & operator=(ButtonFactory &&) noexcept = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::par::ButtonFactoryParameters const & m_params;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_FACTORY_H
