#ifndef _FACE_LEFT_COMMAND_H
#define _FACE_LEFT_COMMAND_H

#include "BaseCommand.h"

namespace app::cmnd
{
	class FaceLeftCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		FaceLeftCommand(app::Entity const _entity);
		virtual ~FaceLeftCommand() = default;

		FaceLeftCommand(FaceLeftCommand const &) = default;
		FaceLeftCommand & operator=(FaceLeftCommand const &) = default;

		FaceLeftCommand(FaceLeftCommand &&) = default;
		FaceLeftCommand & operator=(FaceLeftCommand &&) = default;


	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() override;
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
		app::Entity const m_entity;
	};
}

#endif // !_FACE_LEFT_COMMAND_H
