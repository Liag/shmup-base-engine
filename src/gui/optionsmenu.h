/*
/ Options menu
/ Author: Victor Rådmark
/ Created: 2011-02-14
/ Updated: 2011-02-16
/ License: GPL v3
*/
#ifndef OPTIONSMENU_H_INCLUDED
#define OPTIONSMENU_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "../graphics/particlesystem.h"
#include "../graphics/imagehandler.h"
#include "../sys/configreader.h"
#include "menu.h"

namespace sbe
{
    class OptionsMenu : public sbe::Menu
    {
        public:
            OptionsMenu(void* callObject,
                        void (*applyFunction) (void* object),
                        void (*backFunction) (void* object),
                        const std::string& psFile,
                        ImageHandler* imgHandler,
                        ConfigReader* cReader,
                        const sf::Vector2i& r,
                        const sf::Font& font,
                        const sf::Vector2f& psPos = sf::Vector2f(-1, -1),
                        const sf::Vector2i& next = sf::Vector2i(-1, -1));
            ~OptionsMenu() {}

        private:
            ConfigReader* cfgReader;
            static void incrRes(void* object);
            static void decrRes(void* object);
            static void toggleFS(void* object);
            static void toggleVSync(void* object);
            void setRes(const bool& incr);
            void setFS();
            void setVS();
    };
}

#endif
