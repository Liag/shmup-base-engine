/*
/ Event handler class
/ Author: Jonathan Orr�
/ File created: 2010-11-30
/ File updated: 2010-12-22
/ License: GPLv3
*/

#include <map> //For maps

#include "eventhandler.h" //Class def

namespace sbe
{
    EventHandler::EventHandler()
    {

    }

    //Returns what buttons are being pressed
    void EventHandler::returnEvents(const sf::Event& evt, boolMap& keyReleased)
    {
        if(evt.Type == sf::Event::KeyReleased)
        {
            if (isKeyReleased(sf::Key::Escape, evt))
                    keyReleased["Escape"] = true;
            if (isKeyReleased(sf::Key::L, evt))
                    keyReleased["L"] = true;
            if (isKeyReleased(sf::Key::B, evt))
                    keyReleased["B"] = true;
            if (isKeyReleased(sf::Key::P, evt))
                    keyReleased["P"] = true;
            if (isKeyReleased(sf::Key::R, evt))
                    keyReleased["R"] = true;
            if (isKeyReleased(sf::Key::I, evt))
                    keyReleased["I"] = true;
            if (isKeyReleased(sf::Key::F1, evt))
                    keyReleased["F1"] = true;
        }

    }

    bool EventHandler::isKeyReleased(const sf::Key::Code& key, const sf::Event& evt)
    {
        if((evt.Type == sf::Event::KeyReleased) && (evt.Key.Code == key))
            return true;
        else
            return false;
    }
}
