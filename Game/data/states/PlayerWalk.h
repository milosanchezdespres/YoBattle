#pragma once

#include "../../Components/StateMachine.h"
#include "../../Entities/Entity2D.h"

namespace YoBattleGame
{
    namespace ECS
    {
        struct Character;

        struct PlayerWalk : public State
        {
            Vector2i target_tile;
            Vector2 target;

            float* x;
            float* y;
                    
            int dx[4] = { 0,  0, -1, 1 };
            int dy[4] = {-1,  1,  0, 0 };

            float speed;

            PlayerWalk(Entity* __owner) : State("walk", __owner)
            {
                x = nullptr;
                y = nullptr;

                target = {0, 0};
                target_tile = {0, 0};

                speed = 0;
            }

            void OnEnter() override
            {
                if (parent()->axis == -1) { does<PlayerIdle>(); return; }

                speed = owner<Entity2D>()->get<StateMachine>("states")->move_speed;

                x = &owner<Entity2D>()->get<Sprite>("body")->x;
                y = &owner<Entity2D>()->get<Sprite>("body")->y;
                
                Vector2i current_tile = MAP::screen_to_tile(*x, *y);
                Vector2 snapped_pos = MAP::tile_to_screen(current_tile.i, current_tile.j);
                
                *x = snapped_pos.x;
                *y = snapped_pos.y;
                target_tile = Vector2i(current_tile.i + dx[parent()->axis], current_tile.j + dy[parent()->axis]);

                target = MAP::tile_to_screen(target_tile.i, target_tile.j);
            }

            void OnUpdate(float delta) override
            {
                if(*x != target.x || *y != target.y)
                {
                    float move_delta = speed * delta;

                    if (*x < target.x) *x = min(*x + move_delta, target.x);
                    else if (*x > target.x) *x = max(*x - move_delta, target.x);

                    if (*y < target.y) *y = min(*y + move_delta, target.y);
                    else if (*y > target.y) *y = max(*y - move_delta, target.y);
                }
                else
                {
                    int axis = -1;
                    
                    if(Game::instance().is_down("up")) axis = 0;
                    else if(Game::instance().is_down("down")) axis = 1;
                    else if(Game::instance().is_down("left")) axis = 2;
                    else if(Game::instance().is_down("right")) axis = 3;

                    if(axis != -1)
                    {
                        parent()->axis = axis;

                        Vector2i current_tile = MAP::screen_to_tile(*x, *y);
                        target_tile = Vector2i(current_tile.i + dx[axis], current_tile.j + dy[axis]);
                        target = MAP::tile_to_screen(target_tile.i, target_tile.j);
                    }
                    else { does<PlayerIdle>(); }
                }
            }

            void OnExit() override
            {
                //...
            }
        };
    }
}