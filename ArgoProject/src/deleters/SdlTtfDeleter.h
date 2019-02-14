#ifndef _SDL_TTF_DELETER_H
#define _SDL_TTF_DELETER_H



namespace app::del
{
	class SdlTtfDeleter
	{
	public: // Constructors/Destructor/Assignments
		SdlTtfDeleter() = default;
		~SdlTtfDeleter() = default;

		SdlTtfDeleter(SdlTtfDeleter const &) = default;
		SdlTtfDeleter & operator=(SdlTtfDeleter const &) = default;

		SdlTtfDeleter(SdlTtfDeleter &&) = default;
		SdlTtfDeleter & operator=(SdlTtfDeleter &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(TTF_Font * font) const;
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

	// Unique Pointers
	using UPtrFont = std::unique_ptr<TTF_Font, SdlTtfDeleter>;
}

#endif // !_SDL_TTF_DELETER_H
