#include "stdafx.h"
#include "EntityFactory.h"
#include "Registry.h"

app::fact::EntityFactory::EntityFactory()
	: m_registry(app::Reg::get())
{
}
