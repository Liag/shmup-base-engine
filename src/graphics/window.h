/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-03-23
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream> //Debug output
#include <string> //For strings
#include <map> //Map for objects
#include <list> //For lists

#include <SFML/Graphics.hpp> //Pretty much everything else

#include "../sys/logger.h"
#include "../sys/util.h"
#include "../sys/eventhandler.h" //Event handling
#include "../sys/configreader.h" //Loads settings
#include "../audio/audiohandler.h" //For loading and playing sound and music
#include "../gui/gui.h"
#include "../game/entity.h"
#include "../game/ship.h"
#include "../game/stage.h"
#include "../game/enemy.h"
#include "particlehandler.h"
//#include "../game/player.h"
#include "../game/weapon.h"
#include "../game/enemyhandler.h"   //Enemy handler
#include "drawable.h"
#include "imagehandler.h" //For loading images
#include "background.h" // Background layers

typedef std::list<sbe::Drawable*> RenderList;
typedef std::list<sbe::Panel*> PanelList;

namespace sbe
{
    class Window : public sf::RenderWindow, public sbe::FileHandler
    {
        /*
            The Window class is simply an extension of the default RenderWindow class that acts as the container for the rest of the game.
        */
        public:
            Window(sf::VideoMode Mode, //The video mode of the window, used for res etc
                   ConfigReader* reader, //Loads all the settings and stuff
                   int respawned = 0, //If optionsmenu should be loaded first
                   unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close, //Style of the window, used for fullscreen etc
                   const sf::WindowSettings& Params = sf::WindowSettings()); //Setting params, used for stuff like bit depth and AA
            ~Window();

            int exec(); //Main game loop, returns respawn

        private:
            static void select(void* object);
            static void load(void* object, const std::string& map);
            static void options(void* object);
            static void hiscore(void* object);
            static void credits(void* object);
            static void apply(void* object);
            static void back(void* object);
            static void console(void* object);

            static void exit(void* object);
            static void pauseG(void* object);
            static void flyR(void* object);
            static void flyL(void* object);
            static void flyU(void* object);
            static void flyD(void* object);
            static void startFire(void* object);
            static void stopFire(void* object);
            static void defShipMod(void* object);
            static void othShipMod(void* object);

            void loadStuff(const std::string& map = "");
            void showOptions();
            void showSelect();
            void showHiScore() {}
            void showCredits() {}
            void applyOptions();
            void goBack();
            void showConsole()
            {
                gui->showConsole();
            }

            //void gameOver();

            void pauseGame();
            void flyShip(const Ship::Dir& dir)
            {
                testShip->fly(dir);
            }
            void shipFire(bool start = 1)
            {
                start ? wpn1->startFiring() : wpn1->stopFiring();
            }
            void setShipMod(bool set = 0)
            {
                testShip->setMod(set);
            }

            sbe::ImageHandler *imgHandler;
            sbe::AudioHandler *audHandler;
            sbe::EnemyHandler *enmHandler;
            sbe::EventHandler *evtHandler;
            sbe::ConfigReader *cfgReader;
            sbe::ParticleHandler *prcHandler;
            sbe::Gui *gui;
            std::map<std::string, Ship> ships;
            sbe::Ship *testShip;
            sbe::ParticleSystem *pSystem2;
            sbe::Weapon *wpn1;
            sbe::Music *loli;
            sbe::Background *scroll; // test
            sbe::Enemy* enm1;
            sbe::Stage* stage;

            sbe::Movable *text1;
            sbe::Movable *text2;

            sf::Vector2i res;
            bool respawn,
                 pause,
                 menu,
                 displayText;

            RenderList renderList;
            std::list<Projectile> projectileList;
    };
}

#endif
