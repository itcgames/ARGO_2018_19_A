#ifndef _COMP_CHARACTER_TYPE
#define _COMP_CHARACTER_TYPE

namespace app::comp
{
	struct CharacterType
	{
		enum class Type
		{
			AXE,
			DISC,
			BOMB,
			SWORD_LEGS
		};
	public: // Constructors/Destructor/Assignments
		CharacterType() = default;
		~CharacterType() = default;

		CharacterType(CharacterType const &) = default;
		CharacterType & operator=(CharacterType const &) = default;

		CharacterType(CharacterType &&) = default;
		CharacterType & operator=(CharacterType &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		Type m_type;
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

#endif // !_COMP_CHARACTER_TYPE
