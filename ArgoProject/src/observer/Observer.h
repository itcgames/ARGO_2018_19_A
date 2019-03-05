#ifndef _OBSERVER_H
#define _OBSERVER_H

#include "singletons/AudioPlayerSingleton.h"

enum SubjectEvent {
	PLAYAUDIO
};

namespace app::obs
{
	class Observer
	{
	public: // Constructors/Destructor/Assignments
		//Observer() = default;
		virtual ~Observer() {};

		//Observer(Observer const &) = default;
		//Observer & operator=(Observer const &) = default;

		//Observer(Observer &&) = default;
		//Observer & operator=(Observer &&) = default;

		virtual void notify(std::string s, SubjectEvent event) = 0;
	public: // Public Static Functions
	public: // Public Member Functions
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
	};
	struct Listener {
		static std::vector<Observer*> Obs;
		static void onNotify(std::string s, SubjectEvent event)
		{
			for (auto& observer : app::obs::Listener::Obs)
			{
				observer->notify(s, event);
			}
		}
	};

	class AudioObserver : public Observer
	{

	public: // Constructors/Destructor/Assignments
		AudioObserver();
		void notify(std::string s, SubjectEvent event);
	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		app::gra::AudioPlayer & m_audioPlayer;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables

	};


	class Subject
	{
	public:
		void onNotify(std::string s, SubjectEvent event)
		{
			for (auto& observer : app::obs::Listener::Obs)
			{
				observer->notify(s, event);
			}
		}
		void addObs(app::obs::Observer* obs)
		{
			app::obs::Listener::Obs.push_back(obs);
		}
	};
}



#endif // !_OBSERVER_H
