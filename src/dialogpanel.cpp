/*
/ Dialog panels, for dialogue.
/ Author: Victor Rådmark
/ Created: 2011-01-31
/ Updated: 2011-02-01
/ License: GPL v3
*/
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "dialogpanel.h"
#include "window.h"

namespace sbe
{
    DialogPanel::DialogPanel(const sf::Vector2i& res, const std::vector<std::string>& dialog, const sf::Font& font, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
        : curDiag(0), dialogue(dialog)
    {
        panelRect = new sf::Shape(sf::Shape::Rectangle(sf::Vector2f(20, res.y - 170), sf::Vector2f(600 + res.x / 4, res.y - 20), color, outline, outlineColor));
        createString("dialogString", dialog.at(curDiag), font, 24, sf::Vector2f(30, res.y - 160));
        createButton("nextButton", next, sf::Vector2f(530 + res.x / 4, res.y - 60), 60, "Next", font);
    }

    void DialogPanel::createButton(const std::string& name, void (*callFunction) (void* object), const sf::Vector2f& p, const int& width, const std::string& text, const sf::Font& font, const sf::Color& txtCol,  const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        /*
            Purpose: Create a new button based on parameters, many of which are default.
        */
        sbe::Button tmpBtn(this, callFunction, sf::String(text, font, 20), txtCol, p, sf::Vector2f(p.x + width, p.y + 30), color, outline, outlineColor);
        buttons[name] = tmpBtn;
    }

    void DialogPanel::next(void* object)
    {
        /*
            Go to the next line of dialogue in the called panel.
        */
        //Explicitly cast to a pointer to Window
        DialogPanel* self = (DialogPanel*) object;

        //Call member
        self->setDialog();
    }

    void DialogPanel::setDialog()
    {
        if(curDiag + 1 != dialogue.size())
        {
            strings["dialogString"].SetText(dialogue.at(++curDiag));
            if(curDiag + 1 == dialogue.size())
                buttons["nextButton"].setTextColor(sf::Color(100, 100, 120, 255));
        }
    }
}