#include "stdafx.h"
#include "SplashScene.h"
#include "factories/scenes/SplashSceneFactory.h"
#include "components/AnimatedImage.h"

app::sce::SplashScene::SplashScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::DebugSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::LoadingSystem>),
			UpdateSystem(std::in_place_type<app::sys::DestroySystem>)
		})

		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
{
	using TextureKey = app::res::TextureKey;
	m_resourceManager.loadTexture(TextureKey::Splash, "./res/Animations/splash.png");
	m_resourceManager.loadTexture(TextureKey::Loading, "./res/Animations/loading.png");
	m_resourceManager.loadTexture(TextureKey::Debug, "./res/image.png");
	m_resourceManager.loadTexture(TextureKey::DebugBig, "./res/BigImage.png");
	m_resourceManager.loadTexture(TextureKey::DebugAnimation, "./res/Animations/test.png");
	m_resourceManager.loadTexture(TextureKey::DebugEnemyAnimation, "./res/Animations/testEnemy.png");
	m_resourceManager.loadTexture(TextureKey::DebugCollisionBox, "./res/Debug/colBox.png");
	using FontKey = app::res::FontKey;
	m_resourceManager.loadFont(FontKey::Debug, "./res/Fonts/arial.ttf");
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE Constructed");
	}
}

void app::sce::SplashScene::start()
{
	m_registry.destruction<comp::AnimatedImage>().connect<app::sce::SplashScene, &app::sce::SplashScene::onAnimatedImageDestroy>(this);
	auto const & entities = fact::sce::SplashSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::SplashScene::end()
{
	m_registry.destruction<comp::AnimatedImage>().disconnect<app::sce::SplashScene, &app::sce::SplashScene::onAnimatedImageDestroy>(this);
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

void app::sce::SplashScene::update(app::time::seconds const & dt)
{
	BaseScene::update(dt);
	if (m_resourceManager.isLoaded() && m_splashFinished)
		m_sceneManagerType = SceneType::MainMenu;
	else if (m_splashFinished)
		m_sceneManagerType = SceneType::Loading;
}

void app::sce::SplashScene::onAnimatedImageDestroy(app::Registry & registry, app::Entity const entity)
{
	m_splashFinished = true;
}

