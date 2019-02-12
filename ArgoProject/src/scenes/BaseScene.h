#ifndef _BASE_SCENE_H
#define _BASE_SCENE_H

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
#include "systems/CollisionSystem.h"
namespace app::sce
{
	enum class SceneType
	{
		CharacterSelect,
		Credits,
		Level,
		LevelSelect,
		MainMenu,
		LobbySelect,
		Lobby,
		MultiplayerLevel,
		TutorialLevel,
		Splash,
		Count
	};
	class BaseScene
	{
	protected: // Protected typedefs/Enums/Usings
		using UpdateSystem = std::variant<
			  sys::MotionSystem
			, sys::AirMotionSystem
			, sys::DashSystem
			, sys::StateMachineSystem
			, sys::CameraSystem
			, sys::CommandSystem
			, sys::InputSystem
			, sys::CollisionSystem>;

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
