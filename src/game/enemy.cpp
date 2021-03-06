/*
/ Enemy class
/ Author: Jonathan Orr�, Niklas Andr�asson
/ File created: 2011-03-04
/ File updated: 2011-03-14
/ License: GPLv3
*/
#include "enemy.h"
#include "../sys/logger.h" //Outputs debug in console and log
#include "../sys/util.h"

namespace sbe
{
    Enemy::Enemy(ImageHandler* imgHandler, const std::string spriteName, Path pth, float r, std::string pSysExpl, int l, float scale_x, float scale_y)
    : Ship(spriteName, imgHandler, pSysExpl, r)
    {
        path = pth;
        i = 0;
        sbe::Sprite::SetCenter(sbe::Sprite::GetSize().x/2, sbe::Sprite::GetSize().y/2);
        life = l;
        sbe::Sprite::SetScale(scale_x, scale_y);
        //hitbox = new Hitbox(hitBoxRadius);
    }

    Enemy::~Enemy()
    {
        //safeDelete(hitbox);
    }

    void Enemy::update(const float elapsed)
    {
        if(pSysDeath != NULL)
        {
            pSysDeath->update(elapsed);
        }

        //Timers for two different movements
        Time        += elapsed;
        OrientTime  += elapsed;

        //Duration for one path
        duration = path.getVector()[i].duration;

        //If enemies rotation will follow path
        orientation = path.getVector()[i].orientation;

        //Duration for rotation
        orientDuration = path.getVector()[i].orientDuration;

        //Start & stop angle for enemy
        startAngle = path.getVector()[i].startAngle;
        stopAngle = path.getVector()[i].stopAngle;

        //Start & stop angle for enemy orientation
        orientStart = path.getVector()[i].orientStart;
        orientStop = path.getVector()[i].orientStop;

        //Set enemies speed
        speed = path.getVector()[i].moveSpeed;

        //Will it stop or loop at end of orientation
        stopMax = path.getVector()[i].stopMax;

        if(deathTimer != -1){
            deathTimer -= elapsed;
        }

        //Changes path when duration time reached
        if(Time > duration && i != (path.getVector().size()-1)){
            i++;
            Time = 0;
        }

        //If stopMax == 0 and orientDuration is reached reset clock
        if(OrientTime > orientDuration && stopMax == 0){
            OrientTime = 0;
        }

        //enemy angle is set to startAngle
        angle = startAngle;
        orientmin = orientStart;
        dir = 0;

        //Checks which way the enemy is to turn
        if(startAngle > stopAngle){
            maxangle = startAngle - stopAngle;
            dir = 1;
        }
        else
            maxangle = stopAngle - startAngle;

        //Checks which way the enemy is to rotate
        if(orientStart > orientStop){
            orientmax = orientStart - orientStop;
            orientDir = 1;
        }
        else
            orientmax = orientStop - orientStart;

        //Makes enemy go in a straight line after last path
        if(Time > duration){
            maxangle = 0;
            angle = stopAngle;
        }

        //Calculates how much the enemy is to move based on elapsed time
        if(Time == 0)
        {
            angleTime = 1;
        }else{
            angleTime = Time/duration;
        }
        //Calculates how much the enemy is to rotate based on elapsed time
        rotationTime = OrientTime/orientDuration;

        //Changes the angle based on elapsed time
        if(dir == 1)
            angle -= maxangle*angleTime;
        else
            angle += maxangle*angleTime;

        //Changes the orientation based on elapsed time
        if(orientDir == 1 && orientation == 1)
            orientmin -= orientmax*rotationTime;
        else if(orientation == 1)
            orientmin += orientmax*rotationTime;

        //If stopMax == 1 then stop at maxorientation angle
        if(orientStop <= orientmin && stopMax == 1)
            orientmin = orientStop;

        //Sets rotation for enemy
        sbe::Sprite::SetRotation(-(angle+90+orientmin));

        //Moves the enemy
        Move( (cos((angle) / (180/PI)) * speed) * elapsed,(sin((angle) / (180/PI)) * speed) * elapsed);

        sf::Color col = GetColor();
        if( col.b + 20 > 255 )
        {
            col.b = 255;
            col.g = 255;
        }
        else if(col.b < 255)
        {
            col.b += 20;
            col.g += 20;
        }
        SetColor( col );
    }

    float Enemy::xPos() {
        return GetPosition().x;
    }

    float Enemy::yPos() {
        return GetPosition().y;
    }

    float Enemy::isDead()
    {
        if(life <= 0)
        {
            return true;
        }else
        {
            return false;
        }
    }

    void Enemy::hit()
    {
        sf::Color col = GetColor();
        col.r = 255;
        col.b = 0;
        col.g = 0;
        SetColor( col );

        life--;
    }
}
