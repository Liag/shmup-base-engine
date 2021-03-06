/*
/ Dialog panels, for dialogue.
/ Author: Victor Rådmark
/ Created: 2011-01-31
/ Updated: 2011-02-11
/ License: GPL v3
*/
#ifndef DIALOGPANEL_H_INCLUDED
#define DIALOGPANEL_H_INCLUDED

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "panel.h"

namespace sbe
{
    class DialogPanel : public sbe::Panel
    {
        public:
            DialogPanel(const sf::Vector2i& res, const std::vector<std::string>& dialog, const sf::Font& font, const sf::Color& color = sf::Color(20, 20, 20, 126), const float& outline = 1, const sf::Color& outlineColor = sf::Color::Black);
            ~DialogPanel() {}
            void createButton(const std::string& name,
                              void (*callFunction) (void* object),
                              const sf::Vector2f& p,
                              const int& width,
                              const std::string& text,
                              const sf::Font& font,
                              const sf::Color& txtCol = sf::Color(200, 200, 220, 255),
                              const sf::Color& color = sf::Color(80, 80, 80, 126),
                              const float& outline = 1,
                              const sf::Color& outlineColor = sf::Color(200, 200, 220, 255));
        private:
            static void next(void* object);
            static void previous(void* object);
            void setDialog(bool next = 1);

            unsigned int curDiag;
            std::vector<std::string> dialogue;
    };
}

#endif
