/*
/ Select menu
/ Author: Victor Rådmark
/ Created: 2011-03-12
/ Updated: 2011-03-18
/ License: GPL v3
*/
#ifndef SELECTMENU_H_INCLUDED
#define SELECTMENU_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "menu.h"

namespace sbe
{
    class SelectMenu : public sbe::Menu
    {
        public:
            SelectMenu();
            SelectMenu(void* callObject,
                       void (*loadFunction) (void* object, const int& map),
                       void (*backFunction) (void* object),
                       ConfigReader* cReader,
                       const sf::Vector2i& r,
                       const sf::Font& font);
            ~SelectMenu() {}

            int getSelected();

        private:
            static void loadLevel(void* object);

            void load(const int& map = 0);

            void *funcObject;
            void (*loadFunc) (void* object, const int& map);
    };
}

#endif