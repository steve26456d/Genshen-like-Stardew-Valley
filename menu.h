#pragma once
#ifndef MENU_H
#define MENU_H

#include<cocos2d.h>


class GameMenu:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void AddLabel(cocos2d::Label*& label,std::string str,cocos2d::Vec2 location,float fontSize);

	CREATE_FUNC(GameMenu);
private:
	cocos2d::Label* label_farm = nullptr;
	cocos2d::Label* label_cook = nullptr;
	cocos2d::Label* label_mine = nullptr;
	cocos2d::Label* label_fish = nullptr;
	cocos2d::Label* label_skill = nullptr;
};

extern int FishingProMaxPoint;
#endif // !MENU_H
