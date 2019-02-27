#ifndef _APP_CONSOLE_H
#define _APP_CONSOLE_H

#include "variant.h"

namespace app
{
	/// 
	/// @brief Console class with static functions to write to console window.
	/// @author Rafael Plugge
	/// 
	/// Contains static functions that make debug messages easier to write.
	/// Automatically stops outputting to console if not in debug mode.
	/// 
	class Console
	{
	public: // Usings/Typedefs/enums
		using Variant = std::variant<
			  std::string
			, std::uint8_t
			, std::uint16_t
			, std::uint32_t
			, std::uint64_t
			, std::int8_t
			, std::int16_t
			, std::int32_t
			, std::int64_t
			, std::float_t
			, std::double_t
		>;
	public: // Constructors/Destructor/Assignments
	public: // Public Static Functions
		#ifdef _DEBUG

		/// <summary>
		/// Output to the console the passed text.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only reference to the text that will be output'd to console.</param>
		static inline void write(Variant const & text)
		{
			std::visit(app::util::overload{
				  [](std::string const & txt) { std::cout << txt; }
				, [](auto const & num) { std::cout << std::to_string(num); }
			}, text);
		}

		/// <summary>
		/// Output to the console the collection of text passed.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void write(std::initializer_list<Variant> const & texts) { for (auto const & text : texts) { write(text); } }

		/// <summary>
		/// Output to the console a empty new line.
		///
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		static inline void writeLine() { std::cout << std::endl; }

		/// <summary>
		/// Output to the console the passed text, ending with a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only refernece to the text that will be output'd to console.</param>
		static inline void writeLine(Variant const & text) { write(text); std::cout << std::endl; }

		/// <summary>
		/// Output to the console the collection of text, after which adds a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void writeLine(std::initializer_list<Variant> const & texts) { for (auto const & text : texts) { write(text); } std::cout << std::endl; }

		#else

		/// <summary>
		/// Output to the console the passed text.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only reference to the text that will be output'd to console.</param>
		static inline void write(Variant const & text) {}

		/// <summary>
		/// Output to the console the collection of text passed.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void write(std::initializer_list<Variant> const & texts) {}

		/// <summary>
		/// Output to the console a empty new line.
		///
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		static inline void writeLine() {}

		/// <summary>
		/// Output to the console the passed text, ending with a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="text">read-only refernece to the text that will be output'd to console.</param>
		static inline void writeLine(Variant const & text) {}

		/// <summary>
		/// Output to the console the collection of text, after which adds a new line.
		/// 
		/// This function does nothing when _DEBUG is not defined.
		/// </summary>
		/// <param name="texts">read-only reference to the collection of text that will be output'd to console.</param>
		static inline void writeLine(std::initializer_list<Variant> const & texts) {}

		#endif
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
}

#endif // !_APP_CONSOLE_H
