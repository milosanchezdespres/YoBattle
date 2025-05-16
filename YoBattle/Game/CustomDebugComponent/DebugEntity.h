#pragma once

#include "../../ECS/Entity.h"
#include "DebugComponent.h"

namespace ECS
{
	struct DebugEntity : public Entity
	{
		DebugEntity() : Entity() { OnInit(); }
		DebugEntity(string alias) : Entity(alias) { OnInit(); }

		void OnSetup() override
		{
			attach<Component>();
			attach<DebugComponent>();

			//...
		}

		void OnLoadComponent(json component_json) override
		{
			Entity::OnLoadComponent(component_json);

			if (component_json["alias"] == "DebugComponent")
			{
				attach<DebugComponent>();
				component<DebugComponent>()->standalone_load_from_current_json(component_json);
			}

			//...
		}
	};
}