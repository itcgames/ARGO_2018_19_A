#ifndef _COMP_SEEK_ENTITY_H
#define _COMP_SEEK_ENTITY_H

namespace app::comp
{
	struct SeekEntity
	{
	public: // Constructors/Destructor/Assignments
		SeekEntity() = default;
		SeekEntity(SeekEntity const &) = default;
		SeekEntity(SeekEntity &&) = default;

		~SeekEntity() = default;

		SeekEntity & operator=(SeekEntity const &) = default;
		SeekEntity & operator=(SeekEntity &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		app::Entity entity;
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

#endif // !_COMP_SEEK_ENTITY_H
