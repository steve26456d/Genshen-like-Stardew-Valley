#pragma once
#ifndef _OTHERSCENE_H_
#define _OTHERSCENE_H_
#include"cocos2d.h"
#include"HelloWorldScene.h"
class Desert : public HelloWorld 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float delta) override;              //重写的更新函数


	CREATE_FUNC(Desert);
};
#endif

class City : public HelloWorld
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float delta) override;

	void ChangeSeason(float delta) override;

	CREATE_FUNC(City);
};

class Home : public HelloWorld
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float delta) override;

	CREATE_FUNC(Home);
};