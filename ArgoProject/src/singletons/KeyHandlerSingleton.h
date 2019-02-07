#ifndef _KEY_HANDLER_SINGLETON_H
#define _KEY_HANDLER_SINGLETON_H

namespace app::sin
{
	class KeyHandler
	{
	public: // Constructors/Destructor/Assignments
		KeyHandler() = default;
		~KeyHandler() = default;

		KeyHandler(KeyHandler const &) = default;
		KeyHandler & operator=(KeyHandler const &) = default;

		KeyHandler(KeyHandler &&) = default;
		KeyHandler & operator=(KeyHandler &&) = default;

	public: // Public Static Functions
		static app::inp::KeyHandler & get();
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
		static std::unique_ptr<app::inp::KeyHandler> s_keyHandler;
	private: // Private Member Variables
	};
}

#endif // !_KEY_HANDLER_SINGLETON_H
