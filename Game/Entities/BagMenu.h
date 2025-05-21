#pragma once

#include "../../RetroCS/RetroCS.h"

#include "BaseVerticalMenu.h"
//...

namespace YoBattleGame
{
    namespace ECS
    {
        struct BagMenu : public BaseVerticalMenu
        {
            BaseUI* start_menu;
            BaseUI* bag_ui;

            BagMenu () : BaseVerticalMenu() { }

            void test(string testvar) { cout << testvar << endl; }

            void OnInit()
            {
                BaseVerticalMenu::OnInit();

                execute_on_select = true;
            }

             //MEDALS => ABILITIES
            //EQUIPMENTS => CHIPS/RAM/BATTERY - CHIPS -> INCREASE/DEC. A STAT, MANDATORY FOR IT TO BE USABLE, RAM -> NUMBER OF MEDAL YOU CAN EQUP - BATTERY -> ENERGY FOR TURN -> NB OF ABILITY YOU CAN USE
            
            void OnChoiceAdd() override
            {
                add_choice("items", &BagMenu::test, string("items"));
                add_choice("medals", &BagMenu::test, string("medals"));  
                add_choice("chips", &BagMenu::test, string("chips"));
                add_choice("rams", &BagMenu::test, string("rams"));
                add_choice("batteries", &BagMenu::test, string("batteries"));
                add_choice("key items", &BagMenu::test, string("key items"));
            }
        };
    }
}
