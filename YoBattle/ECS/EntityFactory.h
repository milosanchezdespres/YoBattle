#pragma once

#include "Utils.h"

namespace ECS
{
	class Scene;
	struct Entity;

	class EntityFactory
	{
		public:
			EntityFactory() {}

			void factor(Scene* scene, const json& entity_json)
			{
				if (entity_json["type"] == "Entity")
				{
					//need a fix
					//scene->attach<Entity>(entity_json["alias"]);
					//scene->entity<Entity>(entity_json["alias"])->standalone_load_from_current_json(entity_json);
				}

				OnFactor(scene, entity_json);
			}

		protected:
			virtual void OnFactor(Scene* scene, const json& entity_json) {}
	};
}