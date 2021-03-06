/*
/ Base ship class implementation
/ Author: Victor Rådmark
/ File created: 2010-12-23
/ File updated: 2010-12-24
/ License: GPLv3
*/
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "movable.h" //Base class def
#include "ship.h"

namespace sbe
{
    Ship::Ship(const sf::Image& img, const std::string& pSysExpl, float r, const int max, const unsigned int dMod, const unsigned int oMod)
        : Movable(img, 0, 0), hitBoxRadius(r), deathTimer(-1), deathDelay(0), speedV(0, 0), maxSpeed(max), modifier(dMod), xDir(0), yDir(0), defMod(dMod), otherMod(oMod)
    {
        pSysDeath = NULL;
        pSysDeath_f = pSysExpl;
    }

    Ship::Ship(const std::string& imgStr, ImageHandler* iHandler, const std::string& pSysExpl, float r, const int max, const unsigned int dMod, const unsigned int oMod)
        : Movable(imgStr, iHandler, 0, 0), hitBoxRadius(r), deathTimer(-1), deathDelay(0), speedV(0, 0), maxSpeed(max), modifier(dMod), xDir(0), yDir(0), defMod(dMod), otherMod(oMod)
    {
        pSysDeath = NULL;
        pSysDeath_f = pSysExpl;
    }

    Ship::~Ship()
    {
        delete pSysDeath;
    }

    void Ship::Render(sf::RenderTarget& Target) const
    {
        if(deathTimer == -1 || deathTimer >= deathDelay) Movable::Render(Target);

        if(pSysDeath != NULL)
        {
            Target.Draw(*pSysDeath);
        }
    }

    void Ship::kill(float s)
    {
        pSysDeath = new ParticleSystem( pSysDeath_f, imgHandler, 0 );
        pSysDeath->SetPosition(GetSize().x / 2, GetSize().x / 2);
        deathTimer = s;
        deathDelay = s - 0.1;
    }

    void Ship::update(const float& elapsed)
    {
        /*
            Purpose: Updates the ship's position each frame.
            It checks the previously set xDir and yDir vars and checks the current speed
            which makes for a nice flying algorithm.
        */
        if(pSysDeath != NULL)
        {
            pSysDeath->update(elapsed);
        }
        if(deathTimer != -1){
            deathTimer -= elapsed;
            return;
        }
        //Use angle method instead
        if(xDir == -1 && speedV.x > (maxSpeed * -1))
            speedV.x--;
        else if(xDir == 1 && speedV.x < maxSpeed)
            speedV.x++;
        else
        {
            if(speedV.x < 0) speedV.x++;
            if(speedV.x > 0) speedV.x--;
        }

        if(yDir == -1 && speedV.y > (maxSpeed * -1))
            speedV.y--;
        else if(yDir == 1 && speedV.y < maxSpeed)
            speedV.y++;
        else
        {
            if(speedV.y < 0) speedV.y++;
            if(speedV.y > 0) speedV.y--;
        }

        xDir = 0;
        yDir = 0;

        Move(speedV.x * elapsed * modifier, speedV.y * elapsed * modifier);
    }

    void Ship::fly(const Dir& dir)
    {
        if(dir == UP)
            yDir = -1; //angle = 90
        else if(dir == DOWN)
            yDir = 1; //angle = 270
        else if(dir == LEFT)
            xDir = -1; //angle = 180
        else
            xDir = 1; //angle = 0
    }
}
