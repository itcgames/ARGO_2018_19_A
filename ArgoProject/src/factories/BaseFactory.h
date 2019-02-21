#ifndef _BASE_FACTORY_H
#define _BASE_FACTORY_H

namespace app::fact
{
	template<typename T>
	class BaseFactory
	{
	public: // Constructors/Destructor/Assignments
		BaseFactory() = default;
		virtual ~BaseFactory() = default;

		BaseFactory(BaseFactory const &) = default;
		BaseFactory & operator=(BaseFactory const &) = default;

		BaseFactory(BaseFactory &&) = default;
		BaseFactory & operator=(BaseFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual T create() abstract;
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

#endif // !_BASE_FACTORY_H
