﻿#ifndef _RESOURCE_HANDLER_H
#define _RESOURCE_HANDLER_H

#include <concurrent_unordered_map.h>
#include "ResourceLoader.h"

namespace app::res
{
	template<typename _Key, typename _Resource, bool _Async, typename _Loader = app::res::ResourceLoader<_Resource>>
	class ResourceHandler
	{
	private: // Private typedefs/enums/usings
		struct ManagedResource
		{
			std::shared_ptr<_Resource> resource;
			std::optional<std::thread> thread;
		};
		typedef concurrency::concurrent_unordered_map<_Key, ManagedResource> AsyncResourceMap;
		typedef std::unordered_map<_Key, std::shared_ptr<_Resource>> SyncResourceMap;
		typedef std::conditional_t<_Async, AsyncResourceMap, SyncResourceMap> ResourceMap;
	public: // Constructors/Destructor/Assignments
		ResourceHandler() = default;
		~ResourceHandler() = default;

		ResourceHandler(ResourceHandler const &) = default;
		ResourceHandler & operator=(ResourceHandler const &) = default;

		ResourceHandler(ResourceHandler &&) = default;
		ResourceHandler & operator=(ResourceHandler &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		std::shared_ptr<_Resource> get(_Key const & key, std::optional<std::string> const & file = std::nullopt);
		void load(_Key const & key, std::string const & file);
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
		ResourceMap m_resourceMap;
	};

	template<typename _Key, typename _Resource, bool _Async, typename _Loader>
	std::shared_ptr<_Resource> ResourceHandler<_Key, _Resource, _Async, _Loader>::get(_Key const & key, std::optional<std::string> const & file)
	{
		if (auto const & result = m_resourceMap.find(key); result != m_resourceMap.end())
		{
			auto & mapValue = result->second;
			if constexpr (_Async)
			{
				if (mapValue.thread.has_value())
				{
					mapValue.thread.value().join();
					mapValue.thread.reset();
				}
				return mapValue.resource;
			}
			else
			{
				return mapValue;
			}
		}
		else
		{
			if (!file.has_value()) { std::exception("ERROR in 'ResourceHandler::get': key not found"); }
			this->load(key, file.value());
			return this->get(key, file);
		}
	}

	template<typename _Key, typename _Resource, bool _Async, typename _Loader>
	void ResourceHandler<_Key, _Resource, _Async, _Loader>::load(_Key const & key, std::string const & file)
	{
		auto resource = std::shared_ptr<_Resource>();
		if constexpr (_Async)
		{
			m_resourceMap.insert(std::make_pair(key, ManagedResource{ resource, std::thread(&_Loader::load, resource, file) }));
		}
		else
		{
			_Loader::load(resource, file);
			m_resourceMap.insert(std::make_pair(key, resource));
		}
	}

}

#endif // !_RESOURCE_HANDLER_H
