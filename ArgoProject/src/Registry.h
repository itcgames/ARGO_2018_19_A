#ifndef _REGISTRY_H
#define _REGISTRY_H

namespace app
{
	using Entity = std::uint32_t;
	using Registry = ::entt::Registry<Entity>;

	/// 
	/// @brief Represents non-constructable registry.
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// Contains a single static instance of our registry to make access to the registry easier
	/// as well as utilise the singleton pattern to garantee only one registry is ever created.
	/// 
	/// A registry will store all our entities and their components in highly optimised sets to allow for
	/// fast retrieval and iteration of several entities and different combinations of componenents.
	/// </summary>
	class Reg
	{
	private: // Constructors/Destructor/Assignments
	public: // Public Static Functions
		static Registry & get();
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
		static std::unique_ptr<Registry> s_registry;
	private: // Private Member Variables
	};
}

#endif // !_REGISTRY_H
