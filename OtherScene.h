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