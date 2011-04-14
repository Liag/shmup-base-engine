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
                //: hitbox(NULL)
            {}
            Enemy(
                ImageHandler* imgHandler,
                const std::string spriteName,
                Path pth,
                float r,
                std::string pSysDeath,
                float scale_x,
                float scale_y
            );
            ~Enemy();
            int returnRadius();
            void update(const float& elapsed);
            void kill();
            float xPos();
            float yPos();
            float death();
        private:

            ParticleSystem *pSysDeath;
            std::string pSysDeath_f;

            float hitBoxRadius;
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
                        speed,
                        deathTimer,
                        hej;
            int         orientDir,
                        dir;
            unsigned    i;
            int        alive;
        protected:
            void Render(sf::RenderTarget& Target) const;
    };
}

#endif
