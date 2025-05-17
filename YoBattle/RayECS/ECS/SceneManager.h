#pragma once

namespace ECS
{
	class SceneManager
	{
		protected:
			int __current;
			vector<Scene*> scenes;
			unordered_map<type_index, int> scenesByTypeIndex;

		public:
			SceneManager() { __current = -1; };

			template <typename T>
			void load_scene()
			{
				if (scenesByTypeIndex.find(type_index(typeid(T))) == scenesByTypeIndex.end())
				{
					scenes.push_back(new T());
					scenesByTypeIndex[type_index(typeid(T))] = scenes.size() - 1;
				}
			}

			template <typename T>
			T* scene()
			{
				auto it = scenesByTypeIndex.find(type_index(typeid(T)));
				if (it != scenesByTypeIndex.end()) { return dynamic_cast<T*>(scenes[it->second]); }
				return nullptr;
			}

			Scene* scene() { return scenes[__current]; }

			template <typename T>
			void go_to()
			{
				if (__current != -1) { scene()->Exit(); }

				__current = scenesByTypeIndex[type_index(typeid(T))];

				scene()->Enter();
			}

			~SceneManager() { }
	};
}