#pragma once

#include "../../../../RetroCS/RetroCS.h"

namespace YoBattleGame
{
    namespace DATA
    {
        struct Robot
        {
            Robot()
            {
                int robodex_id;
                string name;

                float base_MP;//MELEE POWER
                float base_RP;//RANGE POWER

                float base_MS;//MELEE SHIELD
                float base_RS;//RANGE SHIELD

                float base_mobility;//he mobility is compared with ennemy, then % are given
                //example : it can give 70% you, 30% opponent. then RNG occurs.

                int token_per_turn;//A TOKEN ALLOWS YOU TO DO SOMETHING ::::::::: ADDING RAM TO YOUR ROBOT INCREASE THIS VALUE
                float bug_probability;//WHEN DOING A MOVE, the robot can 'bug'. this is the % it will occur.
                //applies an increase in MS, decrease in RS;

                float AI;//how fast it xp.
                //applies a decrease on MS, increase on RS;

                //note that bug_probability & AI, at 0, apply nothing.

                //some of these parameters will be modified by chips.

                vector<int> compatible_medals;//which  medals can be equipped.

                //ROBOTS CAN EQUIP UP TO 10 medals. They all start at 4.
            }
        };

        struct RobotData : public DataObject
        {
            RobotData() : DataObject()
            {
                //...
            }
        };
    }
}