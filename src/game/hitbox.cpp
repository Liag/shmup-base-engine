/*
/ Hitbox class
/ Author: Jonathan Orr�, Niklas Andr�asson
/ File created: 2011-04-12
/ File updated: 2011-04-12
/ License: GPLv3
*/

#include "hitbox.h"

namespace sbe
{
    Hitbox::Hitbox(float r)
    {
        radie = r;
    }


    float Hitbox::returnRadie()
    {
        return radie;
    }
}


