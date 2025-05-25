#pragma once

#include "../../Utils/Utils.h"
#include "../../ECS/ECS.h"
#include "../../Window/includes/SimpleCamera.h"

namespace retrocs
{
    namespace window
    {
        bool ___window__logic_initialized;

        struct GameLogic
        {
            Vector4 dest_rect;
            unordered_map<string, vector<drawable*>> batches;
            unordered_map<string, unordered_set<drawable*>> batchesSet;
            unordered_map<drawable*, std::string> reverseLookup;
            
            vector<Entity*> visible_entities;

            Scene* scene;

            GameLogic()
            {
                if (___window__logic_initialized) { throw std::runtime_error("GameData already initialized"); }
                else { ___window__logic_initialized = true; }

                dest_rect = {0, 0, 0, 0};

                scene = nullptr;
            }

            void upload(SimpleCamera* camera, Component* component)
            {
                raw_screen_data* raw_data = component->raw();
                const std::string& key = raw_data->texture;

                // Check if component is already known
                auto revIt = reverseLookup.find(component);

                if (revIt == reverseLookup.end()) 
                {
                    // New component → add to batches[key] and batchesSet[key]
                    batches[key].push_back(component);
                    batchesSet[key].insert(component);
                    reverseLookup[component] = key;
                    return;
                }
                else
                {
                    auto& vec = batches[key];
                    auto it = std::find(vec.begin(), vec.end(), component);
                    if (it != vec.end())
                    {
                        drawable* existingComp = *it;

                        raw_screen_data* newRaw = component->raw();
                        raw_screen_data* existingRaw = existingComp->raw();

                        existingRaw->x = newRaw->x;
                        existingRaw->y = newRaw->y;
                        existingRaw->w = newRaw->w;
                        existingRaw->h = newRaw->h;
                        strcpy(existingRaw->texture, newRaw->texture);
                    }
                }

                const std::string& oldKey = revIt->second;

                if (oldKey != key)
                {
                    // Component is in a different batch → remove from old batch first
                    auto& oldVec = batches[oldKey];
                    auto vecIt = std::find(oldVec.begin(), oldVec.end(), component);
                    if (vecIt != oldVec.end()) {
                        std::iter_swap(vecIt, oldVec.end() - 1);
                        oldVec.pop_back();
                    }

                    batchesSet[oldKey].erase(component);

                    // Add to new batch
                    batches[key].push_back(component);
                    batchesSet[key].insert(component);

                    // Update reverse lookup
                    revIt->second = key;
                }
            }

            void init(Scene* entry_point)
            {
                scene = entry_point->clone(); 

                delete entry_point;
                entry_point = nullptr;

                scene->enter();
            }

            void update()
            {
                //...
                //entity states....
                //scenes systems...

                visible_entities.clear();
                for (Entity* entity : *scene)  { if (entity->is_in_bound()) visible_entities.push_back(entity); }
                for(auto* entity : visible_entities) { if(entity->is_in_bound()) entity->states->update(); }
            }

            void draw(SimpleCamera* camera, BaseGameData* data)
            {
                ::BeginDrawing();
                ::ClearBackground(data->background_color);

                ::BeginBlendMode(BLEND_ALPHA);

                for (const auto& [textureKey, vec] : batches)
                {
                    if (!vec.empty())
                    {
                        Texture2D* texture = data->get<retrocs::window::texture>(textureKey)->data;

                        if (texture)
                        {
                            ::rlSetTexture(texture->id);

                            ::rlBegin(RL_QUADS);
                            ::rlColor4ub(255, 255, 255, 255);

                            for (drawable* comp : vec)
                            {
                                raw_screen_data* raw_data = comp->raw();

                                float x = raw_data->x;
                                float y = raw_data->y;
                                float w = raw_data->w;
                                float h = raw_data->h;

                                comp->___screen_data->in_bound = camera->apply(texture->width, texture->height, x, y, w, h, raw_data->tile_index, dest_rect);
                                bool in_bound = comp->___screen_data->in_bound;

                                if(in_bound)
                                {
                                    if(raw_data->tile_index > -1)
                                    {
                                        ::rlTexCoord2f(dest_rect.x, dest_rect.y);  ::rlVertex3f(x, y, 0);
                                        ::rlTexCoord2f(dest_rect.x, dest_rect.w);  ::rlVertex3f(x, y + h, 0);
                                        ::rlTexCoord2f(dest_rect.z, dest_rect.w);  ::rlVertex3f(x + w, y + h, 0);
                                        ::rlTexCoord2f(dest_rect.z, dest_rect.y);  ::rlVertex3f(x + w, y, 0);
                                    }
                                    else
                                    {
                                        ::rlTexCoord2f(0.0f, 0.0f);
                                        ::rlVertex3f(x, y, 0);

                                        ::rlTexCoord2f(0.0f, 1.0f);
                                        ::rlVertex3f(x, y + h, 0);

                                        ::rlTexCoord2f(1.0f, 1.0f);
                                        ::rlVertex3f(x + w, y + h, 0);

                                        ::rlTexCoord2f(1.0f, 0.0f);
                                        ::rlVertex3f(x + w, y, 0);
                                    }
                                }
                            }

                            ::rlEnd();
                            ::rlSetTexture(0);
                        }
                    }
                }

                __draw_fps();

                ::EndBlendMode();
                ::EndDrawing();
            }

            void __draw_fps()
            {
                int fps = GetFPS();

                std::string fpsText = "FPS: " + std::to_string(fps);

                Vector2 pos = {40.0f, 40.0f};
                int fontSize = 40;
                Color color = WHITE;

                DrawText(fpsText.c_str(), (int)pos.x, (int)pos.y, fontSize, color);
            }


            ~GameLogic() { }
        };
    }
}