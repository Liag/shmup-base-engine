/*
/ Movable class which can move according to angle
/ Author: Victor Rådmark
/ File created: 2011-01-04
/ File updated: 2011-01-07
/ License: GPLv3
*/
#include <iostream>
#include <cmath>

#include "const.h" //Constants
#include "entity.h"
#include "movable.h"

namespace sbe
{
    Movable::Movable(const sf::Image& img, const float& a, const float& s)
        : Entity(img), angle(a), speed(s)
    {

    }

    void Movable::update(const float& elapsed)
    {   //Use elapsed to ensure likewise speed on platforms etc
        Move(cos(angle / (180/PI)) * speed, sin(angle / (180/PI)) * speed);
    }
}