#pragma once
#include"cocos2d.h"
/*
* 名称：主角类
* 作用：实现主角的创建以及移动，交互等的功能
*/
#define HERO_SPEED 25


enum class MyActionTag        //方向标记
{
	MyGoUp = 1,
	MyGoDown,
	MyGoLeft,
	MyGoRight
};