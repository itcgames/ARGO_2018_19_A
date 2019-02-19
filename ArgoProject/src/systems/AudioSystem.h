#ifndef _SYSTEM_AUDIO_H
#define _SYSTEM_AUDIO_H

#include "BaseSystem.h"
#include "graphics/AudioManager.h"

namespace app::sys
{
	class AudioSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		AudioSystem();
		~AudioSystem() = default;

		AudioSystem(AudioSystem const &) = default;
		AudioSystem(AudioSystem &&) = default;

		AudioSystem & operator=(AudioSystem const &) = default;
		AudioSystem & operator=(AudioSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
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
		app::gra::AudioManager m_audioManager;
	};
}

#endif // !_SYSTEM_AUDIO_H
