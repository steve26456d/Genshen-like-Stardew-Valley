#pragma once
#include "cocos2d.h"
#include <string>
using namespace cocos2d;
Animate* getanimation(std::string who,std::string animationname,std::string direction, int Framenum,double frametime);
Sprite* initframe(std::string who, std::string animationname, std::string direction);

