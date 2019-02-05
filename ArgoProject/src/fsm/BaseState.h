#ifndef _FINITE_STATE_MACHINES_BASE_STATE_H
#define _FINITE_STATE_MACHINES_BASE_STATE_H

namespace app::fsm
{
	class BaseState
	{
	public: // Constructors/Destructor/Assignments
		BaseState() = default;
		~BaseState() = default;

		BaseState(BaseState const &) = default;
		BaseState & operator=(BaseState const &) = default;

		BaseState(BaseState &&) = default;
		BaseState & operator=(BaseState &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) abstract;
		virtual void start() abstract;
		virtual void end() abstract;
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
}

#endif // !_FINITE_STATE_MACHINES_BASE_STATE_H
