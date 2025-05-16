#pragma once

#include "../ECS/EntityFactory.h"

namespace ECS
{
	class CustomEntityFactory : public EntityFactory
	{
		public:
			CustomEntityFactory() : EntityFactory() {}

		protected:
			void OnFactor(Scene* scene, const json& entity_json) override
			{
				EntityFactory::OnFactor(scene, entity_json);

				if (entity_json["type"] == "DebugEntity")
				{
					scene->attach<DebugEntity>(entity_json["alias"]);
					scene->entity<DebugEntity>(entity_json["alias"])->standalone_load_from_current_json(entity_json);
				}
			}
	};
}