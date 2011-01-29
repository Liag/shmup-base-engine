/*
/ Base entity class
/ Authors: Felix Westin and Victor Rådmark
/ File created: 2010-12-07
/ File updated: 2010-12-24
/ License: GPLv3
*/
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"

namespace sbe
{
    class Entity : public sf::Sprite
    {
        /*
            Base entity class
        */
        public:
            Entity()
            {

            }
            Entity(const sf::Image& img);
            Entity(const std::string& imgStr, ImageHandler& iHandler);
            ~Entity();

            void setImage(const std::string& imgStr)
            {
                SetImage(imgHandler->getImage(imgStr));
            }

            virtual void update(const float& elapsed) =0; //Or onThink(), whatever.
            void SetAlpha(int alpha);
            void SetDiffuseColor(int r, int g, int b);
            void SetColorR(int r);
            void SetColorG(int g);
            void SetColorB(int b);
            int GetColorR();
            int GetColorG();
            int GetColorB();
            int GetAlpha();
        protected:
            int z;
            ImageHandler* imgHandler;
    };
}

#endif
