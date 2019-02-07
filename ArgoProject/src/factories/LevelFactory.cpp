#include "stdafx.h"
#include "LevelFactory.h"

#include "factories/WallFactory.h"

app::fact::LevelFactory::LevelFactory(app::del::UPtrRenderer const & renderer) {

}

std::optional<app::Entity> app::fact::LevelFactory::create() {
	fact::WallFactory(m_window.getRenderer(), app::math::Vector2f(600, 300)).create();
}