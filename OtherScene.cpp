#include"cocos2d.h"
#include"OtherScene.h"
#include"HelloWorldScene.h"
#include"hero.h"
#include"menu.h"
#include"Bag.h"
#include"animation.h"
#include"Plant.h"
#include"NPC.h"

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

    initMap("desert map/desert.tmx");

    _heroinitPos = { 50,visibleSize.height / 2 + origin.y };
    initHero(_heroinitPos);
    
    //¼üÅÌ¼àÌý
    addListener();

    //Åö×²¼ì²â
    addContact();
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

Scene* City::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = City::create();
    scene->addChild(layer);
    return scene;
}

bool City::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->scheduleUpdate();
    this->schedule(SEL_SCHEDULE(&City::ChangeSeason), 10.0f, kRepeatForever, 0.0f);

    auto director = Director::getInstance();

    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();

    initMap("map/city_normal.tmx");

    initObjects("buildings-cannotgetin", "obstacle", (int)PhysicsCategory::Obstacle, 25);
    initObjects("buildings_caninteract", "build-", (int)PhysicsCategory::Obstacle, 2);
    initObject("buildings_caninteract", "building-market", (int)PhysicsCategory::Obstacle);
    initObjects("buildings_caninteract", "building-NPC-", (int)PhysicsCategory::Obstacle, 4);

    _heroinitPos = { 50,HERO_POSITION.y};
    initHero(_heroinitPos);

    //¼üÅÌ¼àÌý
    addListener();

    //Åö×²¼ì²â
    addContact();
    return true;
}

void City::update(float delta)      //³¡¾°Ö¡¸üÐÂº¯Êý
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

void City::ChangeSeason(float delta)
{
    static int Time = 0;
    Time++;
    if (Time % 3 == 1)
    {
        Season("map/city_normal.tmx");
    }
    else if (Time % 3 == 2)
    {
        Season("map/snow-city-2.tmx");
    }
}

Scene* Home::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Home::create();
    scene->addChild(layer);
    return scene;
}

bool Home::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->scheduleUpdate();
    auto director = Director::getInstance();

    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();

    initMap("map/indoor.tmx");

    initObjects("object", "wall-", (int)PhysicsCategory::Obstacle, 12);
    initObject("object", "cook", (int)PhysicsCategory::CookPoint);

    _heroinitPos = { visibleSize.width / 2 + origin.x,visibleSize.height + origin.y - 100};
    initHero(_heroinitPos);

    //¼üÅÌ¼àÌý
    addListener();

    //Åö×²¼ì²â
    addContact();
    return true;
}

void Home::update(float delta)
{
    auto director = Director::getInstance();

    auto ymax = Director::getInstance()->getVisibleSize().height;  //ÆÁÄ»±ßÔµ
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = this->hero->getPosition();
    //ÆÁÄ»±ßÔµ¼ì²â
    {
        CheckEdge();
    }
    if (abs(heroposition.x - xmax / 2) < 100.0f && abs(heroposition.y - ymax) < 10.0f)
    {
        Director::getInstance()->popScene();
    }
}