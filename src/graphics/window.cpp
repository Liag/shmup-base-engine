/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-03-06
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <string> //For strings
#include <map> //For mapping objects
#include <cstdlib>
#include <list> //For lists

#include <SFML/Graphics.hpp> //Graphics and everything above
#include <SFML/Audio.hpp> //hurr durr

#include "../sys/logger.h"
#include "../sys/util.h"
#include "../sys/eventhandler.h" //Event handling
#include "../sys/configreader.h" //Loads settings
#include "../audio/audiohandler.h" //For loading and playing sound and music
#include "../gui/gui.h"
#include "../game/entity.h"
#include "../game/ship.h"
//#include "../game/player.h"
#include "../game/weapon.h"
#include "drawable.h"
#include "imagehandler.h" //For loading images
#include "particlesystem.h" //Particle system
#include "window.h" //Class def

namespace sbe
{
    Window::Window(sf::VideoMode Mode, ConfigReader* reader, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, reader->getSetting<std::string>("title"), WindowStyle, Params), res(reader->getRes()), respawn(false), pause(false)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        cfgReader = reader;
        SetFramerateLimit(cfgReader->getSetting<int>("limit_fps"));
        UseVerticalSync(cfgReader->getSetting<int>("vsync"));
        menu = cfgReader->getSetting<int>("show_menu");
        Logger::writeMsg(1) << "\nWindow loaded!";

        imgHandler = new ImageHandler();
        audHandler = new AudioHandler();
        audHandler->setMusicVol(cfgReader->getSetting<short>("music_volume"));
        audHandler->setSFXVol(cfgReader->getSetting<short>("sfx_volume"));
        evtHandler = new EventHandler();
        evtHandler->addAction(sf::Key::Escape, this, exit);
        gui = new Gui("scripts/assets/fonts.ast", res);
        Logger::writeMsg(1) << "Handlers loaded!";

        imgHandler->loadAssets("scripts/assets/system_images.ast");
        imgHandler->loadAssets("scripts/assets/images.ast");
        audHandler->loadMusic("scripts/assets/music.ast");
        audHandler->loadSound("scripts/assets/sound.ast");
        Logger::writeMsg(1) << "\nAssets loaded!";

        testShip = NULL;
        pSystem2 = NULL;
        wpn1 = NULL;
        loli = NULL;
        scroll = NULL;

        gui->createMainMenu(this, select, options, hiscore, credits, exit, "scripts/particles/menu/mainmenu.ast", imgHandler, cfgReader, res);
        renderList.push_back(gui);
    }

    Window::~Window()
    {
        /*
            Purpose: Deconstructor for sbe::Window
        */
        renderList.clear();
        delete imgHandler;
        delete audHandler;
        delete evtHandler;
        safeDelete(gui);
        safeDelete(testShip);
        safeDelete(pSystem2);
        safeDelete(wpn1);
        safeDelete(loli);
    }

    bool Window::exec()
    {
        /*
            Purpose: Main game loop, IsOpened with a nicer name basically
        */

        sf::Sound laser(audHandler->getSound("laser"));

        while(IsOpened())
        {
            Logger::write();

            sf::Event event;
            while(GetEvent(event))
            {
                evtHandler->processEvents(event);

                if (event.Type == sf::Event::Closed)
                    Close();
                if(event.Type == sf::Event::MouseButtonReleased)
                    gui->click(sf::Vector2i(GetInput().GetMouseX(), GetInput().GetMouseY()));
            }

            evtHandler->processInput(GetInput());

            if(!menu)
            {
                //Process inputs
                /*GetInput().IsKeyDown(sf::Key::LShift) ? testShip->setMod(30) : testShip->setMod(65);

                if(GetInput().IsKeyDown(sf::Key::Left))
                    testShip->fly(Ship::LEFT);
                else if(GetInput().IsKeyDown(sf::Key::Right))
                    testShip->fly(Ship::RIGHT);

                if(GetInput().IsKeyDown(sf::Key::Up))
                    testShip->fly(Ship::UP);
                else if(GetInput().IsKeyDown(sf::Key::Down))
                    testShip->fly(Ship::DOWN);

                if(GetInput().IsKeyDown(sf::Key::Space) )
                    wpn1->startFiring();
                else
                    wpn1->stopFiring();*/

                pSystem2->SetPosition(testShip->GetPosition().x + testShip->GetSize().x / 2, testShip->GetPosition().y + testShip->GetSize().y / 2);
                wpn1->SetPosition(testShip->GetPosition().x + testShip->GetSize().x / 2, testShip->GetPosition().y + testShip->GetSize().y / 2);
            }

            //Get elapsed time since last frame to ensure constant speed
            float ElapsedTime = GetFrameTime();

            //Update everything
            for(RenderList::iterator it = renderList.begin(); it != renderList.end(); it++)
                if(!pause) (*it)->update(ElapsedTime);

            Clear();

            // Draw stuff
            for(RenderList::const_iterator it = renderList.begin(); it != renderList.end(); it++)
                Draw(**it);

            // Update the window
            Display();
        }

        return respawn;
    }

    void Window::select(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->loadStuff(0);
    }

    void Window::options(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showOptions();
    }

    void Window::hiscore(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showHiScore();
    }

    void Window::credits(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showCredits();
    }

    void Window::exit(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->Close();
    }

    void Window::apply(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->applyOptions();
    }

    void Window::back(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->goBack();
    }

    void Window::pauseG(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->pauseGame();
    }

    void Window::flyR(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::RIGHT);
    }

    void Window::flyL(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::LEFT);
    }

    void Window::flyU(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::UP);
    }

    void Window::flyD(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::DOWN);
    }

    void Window::startFire(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->shipFire();
    }

    void Window::stopFire(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->shipFire(0);
    }

    void Window::defShipMod(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->setShipMod(1);
    }

    void Window::othShipMod(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->setShipMod();
    }

    void Window::showOptions()
    {
        gui->deleteMainMenu();
        gui->createOptionsMenu(this, apply, back, "scripts/particles/menu/options.ast", imgHandler, cfgReader, res, gui->getPSPos(), gui->getNextPSPos());
    }

    void Window::applyOptions()
    {
        respawn = true;
        Close();
    }

    void Window::goBack()
    {
        gui->deleteOptionsMenu();
        gui->createMainMenu(this, select, options, hiscore, credits, exit, "scripts/particles/menu/mainmenu.ast", imgHandler, cfgReader, res, gui->getPSPos(), gui->getNextPSPos());
    }

    void Window::pauseGame()
    {
        loli->GetStatus() != sf::Music::Playing ? loli->Play() : loli->Pause();
        pause = !pause;
        gui->pause();
    }

    void Window::loadStuff(const int& map)
    {
        if(map == 0)
        {
            menu = false;
            renderList.pop_back();
            gui->deleteMainMenu();

            testShip = new sbe::Ship("cross", imgHandler);
            //*ships["testShip"] = *testShip;
            testShip->SetPosition(0.f, 0.f);
            //testShip->SetScale(0.5, 0.5);
            //testShip->SetAlpha(0);

            pSystem2 = new ParticleSystem("scripts/particles/plasma_blast.ast", imgHandler, cfgReader->getSetting<float>("ps_reload"));
            scroll = new Background(cfgReader, "scripts/maps/background.ast", imgHandler);
            wpn1 = new Weapon("scripts/weapons/test_wpn.ast", imgHandler, cfgReader);

            std::vector<std::string> diag;
            diag.push_back("OHAYO");
            diag.push_back("Sugoi sugoi!");
            diag.push_back("VN of the year all years");
            gui->createDialogPanel(res, diag);

            renderList.push_back(scroll);
            renderList.push_back(testShip);
            renderList.push_back(pSystem2);
            renderList.push_back(wpn1);
            renderList.push_back(gui);

            loli = new sbe::Music();
            loli->OpenFromFile(audHandler->getMusic("loli2"));
            loli->SetVolume(audHandler->getMusicVol());
            loli->Play();

            evtHandler->addAction(sf::Key::P, this, pauseG);

            evtHandler->addInputAction(sf::Key::LShift, this, othShipMod, defShipMod);
            evtHandler->addInputAction(sf::Key::Right, this, flyR);
            evtHandler->addInputAction(sf::Key::Left, this, flyL);
            evtHandler->addInputAction(sf::Key::Up, this, flyU);
            evtHandler->addInputAction(sf::Key::Down, this, flyD);
            evtHandler->addInputAction(sf::Key::Space, this, startFire, stopFire);
        }
    }
}
