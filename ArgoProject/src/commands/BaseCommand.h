#ifndef _BASE_COMMAND_H
#define _BASE_COMMAND_H

namespace app::cmnd
{
	class BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		BaseCommand();
		virtual ~BaseCommand() = default;

		BaseCommand(BaseCommand const &) = default;
		BaseCommand(BaseCommand &&) = default;

		BaseCommand & operator=(BaseCommand const &) = default;
		BaseCommand & operator=(BaseCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() abstract;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
		void output(std::string const & message) const;
		void output(std::initializer_list<app::Console::Variant> const & messages) const;
	protected: // Protected Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	protected: // Protected Member Variables
		app::Registry & m_registry;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables

	};
}

#endif // !_BASE_COMMAND_H
