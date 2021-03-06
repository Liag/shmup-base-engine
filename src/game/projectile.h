/*
/ Projectile class
/ Author: Felix Westin
/ File created: 2011-01-29
/ File updated: 2011-01-29
/ License: GPLv3
*/
#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <iostream> //Debug output
#include <fstream> //Read script files
#include <string> //For strings
#include <cstring> //For strcpy
#include <list> //For lists
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/filehandler.h" //Base class
#include "../sys/logger.h" //Outputs debug in console and log
#include "../graphics/imagehandler.h" //For loading images
#include "../graphics/particlesystem.h" //Particle system
#include "../sys/util.h"
#include "../sys/configreader.h"
#include "movable.h"
#include "hitbox.h"


namespace sbe
{
    class Projectile : public Drawable
    {
        /*
        Projectile class
        */
        public:
            Projectile(
                        ImageHandler* imgHandler,
                        ConfigReader* cfgReader,
                        const int&          xPos,
                        const int&          yPos,
                        const sf::Image&    img,
                        const float&        a,
                        const float&        v,
                        const std::string&  pSysFile,
                        const float         radie
                       );
            ~Projectile()
            {
            }
            void update(const float& elapsed);
            void push(const float& distance);
            void SetScale(const float& x, const float& y);
            void SetRotation(const float& r);
            void kill();
            bool isUseless();
            int returnRadius();
            float xPos();
            float yPos();

        protected:
            void Render(sf::RenderTarget& Target) const;
            Hitbox* hitbox;

        private:
            Movable             proj;
            ImageHandler        *imageHandler;
            ConfigReader        *configReader;
            std::string         name,
                                pSystemFile;

            ParticleSystem      *pSys;

            float               hitBoxRadius,
                                damage;
    };
}

#endif
