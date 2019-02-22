#include "stdafx.h"
#include "ButtonMainMenuMultiplayerConnectCancelCommand.h"
#include "components/Destroy.h"
#include "components/Widget.h"

app::cmnd::ButtonMainMenuMultiplayerConnectCancelCommand::ButtonMainMenuMultiplayerConnectCancelCommand(app::Entity const callingEntity)
	: BaseMultiplayerCommand()
	, m_callingEntity(callingEntity)
	, m_entities()
{
}

void app::cmnd::ButtonMainMenuMultiplayerConnectCancelCommand::setEntites(std::vector<app::Entity> const & entities)
{
	m_entities.reserve(m_entities.size() + entities.size());
	m_entities.insert(m_entities.end(), entities.cbegin(), entities.cend());
}

void app::cmnd::ButtonMainMenuMultiplayerConnectCancelCommand::execute()
{
	if (!m_client.hasInit()) { return; }
	if (m_client.deinitNetwork())
	{
		this->output("Disconnection from server successful !");
		for (auto entity : m_entities)
		{
			assert(m_registry.valid(entity));
			m_registry.assign<comp::Destroy>(entity);
		}
		auto widgetView = m_registry.view<comp::Widget>();
		if (widgetView.contains(m_callingEntity))
		{
			auto & widget = widgetView.get(m_callingEntity);
			widget.state = comp::Widget::State::Pressed;
		}
	}
	else
	{
		this->output("Disconnection from server failed !");
	}
}
