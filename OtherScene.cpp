#include"cocos2d.h"
#include"OtherScene.h"
#include"HelloWorldScene.h"
#include"hero.h"
#include"menu.h"
#include"Bag.h"
#include"animation.h"
USING_NS_CC;


Scene* Desert::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Desert::create();
    scene->addChild(layer);
    return scene;
}

bool Desert::init()
{

    if (!Layer::init())
    {
        return false;
    }
    this->scheduleUpdate();
    auto director = Director::getInstance();

    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();

    if(!map)
        map = TMXTiledMap::create("desert map/desert.tmx");
    map->setScale(director->getContentScaleFactor() * 2);              //µ÷Õû´óÐ¡£¬ÊÊÅäÆÁÄ»
    this->addChild(map, 1);

    _heroinitPos = { 50,visibleSize.height / 2 + origin.y };
    initHero(_heroinitPos);
    
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Desert::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Desert::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    return true;
}

void Desert::update(float delta)      //³¡¾°Ö¡¸üÐÂº¯Êý
{
    auto ymax = Director::getInstance()->getVisibleSize().height;  //ÆÁÄ»±ßÔµ
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = hero->getPosition();
    //ÆÁÄ»±ßÔµ¼ì²â
    {
        CheckEdge();
    }
    if (abs(heroposition.x) < 10.0f && abs(heroposition.y - ymax / 2) < 100.0f)
    {
        hero->stopAllActions();
        Director::getInstance()->popScene();
    }
}
