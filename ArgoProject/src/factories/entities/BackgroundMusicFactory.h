#ifndef _BACKGROUND_MUSIC_FACTORY_H
#define _BACKGROUND_MUSIC_FACTORY_H

#include "../EntityFactory.h"

namespace app::fact
{
	class BackgroundMusicFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		BackgroundMusicFactory(
			std::string s
			,app::res::AudioKey const & audioKey);
		virtual ~BackgroundMusicFactory() = default;

		BackgroundMusicFactory(BackgroundMusicFactory const &) = default;
		BackgroundMusicFactory & operator=(BackgroundMusicFactory const &) = default;

		BackgroundMusicFactory(BackgroundMusicFactory &&) = default;
		BackgroundMusicFactory & operator=(BackgroundMusicFactory &&) = default;

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
		app::res::AudioKey const & m_audioKey;
		std::string & const m_name;
	};
}

#endif // !_BACKGROUND_MUSIC_FACTORY_H
