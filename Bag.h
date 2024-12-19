#pragma once
/*
* 作用：背包
* 
* 储存物品，保存物品的图像，数量信息
*/
#ifndef _BAG_H_
#define _BAG_H_
#include<cocos2d.h>
#include"Item.h"
class Bag :public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();    //bag的创造层函数

	virtual bool init();                     //bag的初始化函数

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	                                         //键盘监听函数
	void AddCell(cocos2d::Vec2 Pos);         //生成背包格子的函数
	CREATE_FUNC(Bag);

	//Tag
	static int BagTag;
private:
	cocos2d::Sprite* select_cell = nullptr;  //被选中的格子

	//存储的物品集

	static float BeginX;
	static float EndX;
	static float BeginY;
	static float EndY;

	const int _bag_order = 3;
};
#endif // !_BAG_H_
