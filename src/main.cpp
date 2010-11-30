/*
/ The main function
/ Authors: Victor R�dmark, Felix Westin, Jonathan Orr�
/ File created: 2010-11-14
/ File updated: 2010-11-17
/ License: GPLv3
*/
#include <SFML/Graphics.hpp>

#include "window.h"
#include "configreader.h"

int main()
{
    //Create the config reader
    sbe::ConfigReader *cfgReader = new sbe::ConfigReader();

    sbe::Window *mainWindow;

    if(cfgReader->getFS())
        mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), "SBE Window", sf::Style::Fullscreen);
    else
        mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), "SBE Window");
    // Create the main window


    mainWindow->exec();

    delete mainWindow;

    return 0;
}
