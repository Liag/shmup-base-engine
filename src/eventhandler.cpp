/*
/ Event handler class
/ Author: Jonathan Orr�
/ File created: 2010-11-30
/ File updated: 2010-11-30
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
    std::map<std::string, bool> EventHandler::returnEvents(sf::Event evt)
    {
        if(evt.Type == sf::Event::KeyReleased)
        {
            if (isKeyReleased(sf::Key::Escape, evt))
                    keyReleased["Escape"] = true;
            if (isKeyReleased(sf::Key::L, evt))
                    keyReleased["L"] = true;
            if (isKeyReleased(sf::Key::B, evt))
                    keyReleased["B"] = true;
            if (isKeyReleased(sf::Key::I, evt))
                    keyReleased["I"] = true;
            if (isKeyReleased(sf::Key::F1, evt))
                    keyReleased["F1"] = true;
        }

        return keyReleased;
    }

    bool EventHandler::isKeyReleased(sf::Key::Code key, sf::Event evt)
    {
        if((evt.Type == sf::Event::KeyReleased) && (evt.Key.Code = key))
            return true;
        else
            return false;
    }
}
