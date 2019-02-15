#ifndef _RENDER_TEXT_SYSTEM_H
#define _RENDER_TEXT_SYSTEM_H

#include "BaseSystem.h"
#include "graphics/Window.h"
#include "graphics/RenderText.h"

namespace app::sys
{
	class RenderTextSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		RenderTextSystem();
		virtual ~RenderTextSystem() = default;

		RenderTextSystem(RenderTextSystem const &) = default;
		RenderTextSystem & operator=(RenderTextSystem const &) = default;

		RenderTextSystem(RenderTextSystem &&) = default;
		RenderTextSystem & operator=(RenderTextSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) final override;
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
		app::gra::Window & m_window;
		app::gra::RenderText m_renderText;
		app::gra::View m_view;
	};
}

#endif // !_RENDER_TEXT_SYSTEM_H
