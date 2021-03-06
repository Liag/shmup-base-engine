/*
/ Console panel
/ Author: Victor Rådmark
/ Created: 2011-03-29
/ Updated: 2011-04-12
/ License: GPL v3
*/
#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../sys/logger.h"
#include "panel.h"
#include "command.h"
#include "console.h"

namespace sbe
{
    Console::Console(const sf::Vector2i& res, const sf::Font& f)
        : Panel(sf::Vector2f(1, 1), sf::Vector2f(res.x - 1, res.y / 2), sf::Color(0, 0, 0, 150), 1, sf::Color::White), font(f), active(false), focus(false)
    {
        inStr = new sf::String("> _", font, 14.f);
        inStr->SetColor(sf::Color::White);
        inStr->SetPosition(5, (res.y / 2) - 20);

        addCommand("help", "Display the console help.", this, help);
        addCommand("cmd", "Display a list of all available console commands.", this, cmd);
    }

    Console::~Console()
    {
        //commands.clear();
        history.clear();
        strings.clear();
        delete inStr;
    }

    void Console::addCommand(const std::string& name, const std::string& description, void* callObject, void (*cmdFunction) (void* object))
    {
        Command tmpCmd(description, callObject, cmdFunction);
        commands[name] = tmpCmd;
    }

    void Console::addCommand(const std::string& name, const std::string& description, void* callObject, void (*cmdFunction) (void* object, StrVec args))
    {
        Command tmpCmd(description, callObject, cmdFunction);
        commands[name] = tmpCmd;
    }

    void Console::click(const sf::Vector2i& mousePos)
    {
        focus = true;
    }

    void Console::hover(const sf::Vector2i& mousePos)
    {

    }

    void Console::type(const sf::Uint32& text)
    {
        std::string tmpStr = inStr->GetText();

        if(text == 13)
        {
            if(tmpStr != "> _")
            {
                addString(tmpStr.substr(0, tmpStr.size() - 1));
                exec(tmpStr.substr(2, tmpStr.size() - 3));
            }

            inStr->SetText("> _");
            return;
        }

        if(text != 9)
        {
            if(text != 8 && text != 127) tmpStr.insert(tmpStr.end() - 1, (char) text);
            else if(tmpStr != "> _") tmpStr.erase(tmpStr.end() - 2, tmpStr.end() - 1);
        }

        inStr->SetText(tmpStr);
    }

    void Console::update()
    {
        StrVec tmpLog = Logger::getLog();
        Logger::clearLog();
        if(!tmpLog.empty() && tmpLog.at(0) != "")
        {
            for(unsigned int i = 0; i < tmpLog.size(); i++)
            {
                while(tmpLog.at(i).find("\n") != std::string::npos)
                    tmpLog.at(i).erase(tmpLog.at(i).find("\n"), 1);
                addString(tmpLog.at(i));
            }
        }
    }

    void Console::Render(sf::RenderTarget& target) const
    {
        Panel::Render(target);
        for(unsigned int i = 0; i < strings.size(); i++)
            target.Draw((strings.at(i)));

        target.Draw(*inStr);
    }

    void Console::help(void* object)
    {
        //Explicitly cast to a pointer to Console
        Console* self = (Console*) object;

        //Call member
        self->printHelp();
    }

    void Console::cmd(void* object)
    {
        //Explicitly cast to a pointer to Console
        Console* self = (Console*) object;

        //Call member
        self->printCmds();
    }

    void Console::printHelp()
    {
        addString("_______________");
        addString("SBE version 0.1");
        addString("Console help");
        addString(" ");
        addString("To see a list of all commands, type 'cmd'.");
        addString("For more specific help on a single command, typ 'help <command>'");
        addString("Refer to the enclosed user manual for further instructions.");
    }

    void Console::printCmds()
    {
        addString("_______________");
        addString("SBE version 0.1");
        addString("Console commands");
        addString(" ");
        for(CmdMap::iterator it = commands.begin(); it != commands.end(); it++)
            addString(it->first + " - " + it->second.getDescription());
        //addString("help <command> - display help on a specific command.");
    }

    void Console::exec(std::string cmd)
    {
        StrVec args;

        if(cmd.find(' ') != std::string::npos)
        {
            args.push_back(cmd.substr(cmd.find(' ') + 1, cmd.size() - cmd.find(' ')));
            cmd = cmd.substr(0, cmd.find(' '));

            while(args.back().find(' ') != std::string::npos)
            {
                args.push_back(args.back().substr(args.back().find(' ') + 1 , args.size() - args.back().find(' ')));
                args.at(args.size() - 1) = args.at(args.size() - 1).substr(0, args.at(args.size() - 1).find(' ') - 1);
            }
        }

        if(commands.find(cmd) == commands.end())
        {
            addString("Command '" + cmd + "' not found");
            return;
        }

        if(!commands[cmd].exec(args)) addString("Wrong number of arguments for command '" + cmd + "'.");

    }

    void Console::addString(const std::string& str)
    {
        history.push_back(str);
        int pos = 2;

        if(!strings.empty()) pos = strings.back().GetPosition().y + 16;
        sf::String tmpStr(history.back(), font, 14.f);
        tmpStr.SetColor(sf::Color::White);
        tmpStr.SetPosition(5, pos);
        strings.push_back(tmpStr);

        if(strings.size() > ((unsigned int) ((panelRect.GetPointPosition(2).y - panelRect.GetPointPosition(0).y) / 17))) removeString();
    }

    void Console::removeString()
    {
        strings.erase(strings.begin());
        for(unsigned int i = 0; i < strings.size(); i++)
            strings.at(i).SetPosition(strings.at(i).GetPosition().x, strings.at(i).GetPosition().y - 16);
    }
}
