#ifndef _BASE_SCENE_H
#define _BASE_SCENE_H

#include "SceneType.h"
#include "resources/ResourceManager.h"
#include "systems/AirMotionSystem.h"
#include "systems/AnimatorSystem.h"
#include "systems/CameraSystem.h"
#include "systems/CommandSystem.h"
#include "systems/InputSystem.h"
#include "systems/MotionSystem.h"
#include "systems/RenderSystem.h"
#include "systems/StateMachineSystem.h"
#include "systems/DashSystem.h"
#include "systems/DebugSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/HealthSystem.h"
#include "systems/CurrentGroundSystem.h"
#include "systems/NetworkSystem.h"
#include "systems/ButtonSystem.h"
#include "systems/WidgetNavigationSystem.h"
#include "systems/DestroySystem.h"
#include "systems/AISystem.h"
#include "systems/LoadingSystem.h"

namespace app::sce
{
	class BaseScene
	{
	protected: // Protected typedefs/Enums/Usings
		using UpdateSystem = std::variant<
			  sys::MotionSystem
			, sys::AirMotionSystem
			, sys::DashSystem
			, sys::StateMachineSystem
			, sys::CommandSystem
			, sys::InputSystem
			, sys::CameraSystem
			, sys::CollisionSystem
			, sys::DebugSystem
			, sys::HealthSystem
			, sys::AISystem
			, sys::CurrentGroundSystem
			, sys::LoadingSystem
			, sys::NetworkSystem
			, sys::ButtonSystem
			, sys::WidgetNavigationSystem
			, sys::DestroySystem
		>;
		using UpdateSystems = std::vector<UpdateSystem>;
		using DrawSystem = std::variant<
			  sys::RenderSystem
			, sys::AnimatorSystem
		>;
		using DrawSystems = std::vector<DrawSystem>;
		using ResourceManager = app::res::ResourceManager<true>;
	public: // Constructors/Destructor/Assignments
		BaseScene(SceneType & sceneManagerType, UpdateSystems && updateSystems, DrawSystems && drawSystems);
		virtual ~BaseScene();

		BaseScene(BaseScene const &) = default;
		BaseScene & operator=(BaseScene const &) = default;

		BaseScene(BaseScene &&) = default;
		BaseScene & operator=(BaseScene &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void start() abstract;
		virtual void update(app::time::seconds const & dt);
		virtual void render(app::time::seconds const & dt);
		virtual void end() abstract;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
		constexpr static bool DEBUG_MODE = true;
	protected: // Protected Member Variables
		app::Registry & m_registry;
		SceneType & m_sceneManagerType;
		ResourceManager & m_resourceManager;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		UpdateSystems m_updateSystems;
		DrawSystems m_drawSystems;
	};
}

#endif // !_BASE_SCENE_H
