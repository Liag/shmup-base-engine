/*
/ Enemy class
/ Author: Jonathan Orr�
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "ship.h"
#include "path.h"
#include "hitbox.h"

#include "../graphics/particlesystem.h" //Particle system

namespace sbe
{
    class Enemy : public Ship
    {
        public:
            Enemy()
                : Ship::Ship()
            {}
            Enemy(
                ImageHandler* imgHandler,
                const std::string spriteName,
                Path pth,
                float r,
                std::string pSysExpl,
                int l,
                float scale_x,
                float scale_y
            );
            ~Enemy();
            void update(const float elapsed);
            float xPos();
            float yPos();
            float isDead();
            void hit();
        private:

            //Hitbox* hitbox;
            Path path;
            float       Time,
                        OrientTime,
                        maxangle,
                        duration,
                        orientation,
                        orientDuration,
                        orientStart,
                        orientStop,
                        orientmax,
                        orientmin,
                        startAngle,
                        stopAngle,
                        stopMax,
                        rotationTime,
                        angleTime,
                        angle,
                        speed;
            int         orientDir,
                        dir,
                        life;
            unsigned    i;
    };
}

#endif
