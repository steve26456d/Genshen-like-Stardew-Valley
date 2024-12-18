#include "HelloWorldScene.h"
#include"hero.h"
#include"OtherScene.h"
#include"NPC.h"
#include"menu.h"
#include"Plant.h"
#include"bag.h"
#include"animation.h"
USING_NS_CC;
cocos2d::TMXTiledMap* HelloWorld::map = nullptr;
Sprite* HelloWorld::hero = nullptr;
Object* HelloWorld::collidedSprite = nullptr;
bool HelloWorld::IsCollide = false;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
   
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    
    using namespace cocos2d;
   
    this->scheduleUpdate();
    //this->schedule(SEL_SCHEDULE(&HelloWorld::ChangeSeason),6.0f,kRepeatForever,0.0f);
    
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //初始地图
    if (!map)
        map = TMXTiledMap::create("home map/home.tmx");                  //加载瓦片地图,初始地图 
  
    auto director = Director::getInstance();                       //获得导演
    map->setScale(director->getContentScaleFactor() * 2);              //调整大小，适配屏幕
    
    //加载地图
    this->addChild(map, 1);

    //放置主角
    hero = initframe("qilunuo", "walk", "down");
    hero->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(hero, 3);
    auto herobody = PhysicsBody::createBox(hero->getContentSize());
    herobody->setGravityEnable(false);
    herobody->setDynamic(false);

    //设置位掩码
    herobody->setCategoryBitmask((int)PhysicsCategory::Hero);
    herobody->setContactTestBitmask(0xfffffff);
    herobody->setCollisionBitmask(0);
    hero->setPhysicsBody(herobody);
    hero->stopAllActions();

    //键盘监听
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    //碰撞检测
    auto physicalcontact = cocos2d::EventListenerPhysicsContact::create();
    physicalcontact->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    physicalcontact->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);

    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(physicalcontact, this);

    return true;
}

void HelloWorld::update(float delta)      //场景帧更新函数
{
    auto director = Director::getInstance();
   
    auto ymax = Director::getInstance()->getVisibleSize().height;  //屏幕边缘
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = this->hero->getPosition();
    //屏幕边缘检测
    {
        if (ymax < heroposition.y + 10.f)
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoUp));
            if (repeat)
                this->hero->stopAction(repeat);
        }
        if (xmax < heroposition.x + 10.f)
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoRight));
            if (repeat)
                this->hero->stopAction(repeat);
        }
        if (heroposition.y - 10.0f < 0)
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoDown));
            if (repeat)
                this->hero->stopAction(repeat);
        }
        if (heroposition.x - 10.0f < 0)
        {
            auto repeat = hero->getActionByTag(static_cast<int>(MyActionTag::MyGoLeft));
            if (repeat)
                this->hero->stopAction(repeat);
        }
    }
    if(abs(heroposition.x - xmax) < 10.0f && abs(heroposition.y - ymax / 2) < 100.0f)
    {
        hero->setPosition(heroposition.x - 100.0f, heroposition.y);
        auto desert = Desert::createScene();//下一个场景
        Director::getInstance()->pushScene(desert);
        hero->stopAllActions();
    }
}

void HelloWorld::ChangeSeason(float delta)
{
    static int Time = 0;
    Time++;
    if(Time % 2 == 1)
    {
        auto zorder = map->getLocalZOrder();
        auto newmap = TMXTiledMap::create("desert map/desert.tmx");
        auto director = Director::getInstance();                       //获得导演
        newmap->setScale(director->getContentScaleFactor() * 2);              //调整大小，适配屏幕
        this->removeChild(map, true);
        this->addChild(newmap, zorder);
        map = newmap;
    }
    else if (Time % 2 == 0)
    {
        auto zorder = map->getLocalZOrder();
        auto newmap = TMXTiledMap::create("home map/home.tmx");
        auto director = Director::getInstance();                       //获得导演
        newmap->setScale(director->getContentScaleFactor() * 2);              //调整大小，适配屏幕
        this->removeChild(map, true);
        this->addChild(newmap, zorder);
        map = newmap;
    }
}

void HelloWorld::onExit()
{
    Layer::onExit();
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    static bool IsBag = false;        //检测是否为背包界面，如果为背包界面，人物就无法移动
    static int BagNumber = 0;         //当BagNumber为奇数时，进入背包，当BagNumber为偶数时，离开背包
    static EventKeyboard::KeyCode lastKeycode = EventKeyboard::KeyCode::KEY_0;
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:   //主角向上移动
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.4f, Vec2(0, 4 * HERO_SPEED));
                auto animationaction = getanimation("qilunuo", "walk", "up", 4, 0.1);
                auto repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
                repeat->setTag(static_cast<int>(MyActionTag::MyGoUp));
                this->hero->runAction(repeat);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: //主角向下移动
        case EventKeyboard::KeyCode::KEY_S:
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.4f, Vec2(0, -4 * HERO_SPEED));
                auto animationaction = getanimation("qilunuo", "walk", "down", 4, 0.1);
                auto repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
                repeat->setTag(static_cast<int>(MyActionTag::MyGoDown));
                this->hero->runAction(repeat);
            }

            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: //主角向左移动
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.4f, Vec2(-4 * HERO_SPEED, 0));
                auto animationaction = getanimation("qilunuo", "walk", "left", 4, 0.1);
                auto repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
                repeat->setTag(static_cast<int>(MyActionTag::MyGoLeft));
                this->hero->runAction(repeat);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //主角向右移动
        {
            if(!IsBag)
            {
                auto action = MoveBy::create(0.4f, Vec2(4 * HERO_SPEED, 0));
                auto animationaction = getanimation("qilunuo", "walk", "right", 4, 0.1);
                auto repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
                repeat->setTag(static_cast<int>(MyActionTag::MyGoRight));
                this->hero->runAction(repeat);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE:       //退出程序
        {
            Director::getInstance()->end();
            break;
        }
        case EventKeyboard::KeyCode::KEY_TAB:          //进入技能树页面
        {
            Scene* menu = GameMenu::createScene();
            Director::getInstance()->pushScene(menu);
            break;
        }
        case EventKeyboard::KeyCode::KEY_P:            //种植植物
        {
            if(!IsBag)
            {
                lastKeycode = EventKeyboard::KeyCode::KEY_P;
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_B:            //背包
        {
            if (BagNumber & 1)                         //进入背包
            {
                auto bag = this->getChildByTag(Bag::BagTag);
               
                this->removeChildByTag(Bag::BagTag,true);
                IsBag = false;
            }
            else                                       //离开背包
            {
                auto bag = Bag::createLayer();
                bag->setTag(Bag::BagTag);
                this->addChild(bag, INT_MAX);
                IsBag = true;
            }
            BagNumber++;
            break;
        }
        case EventKeyboard::KeyCode::KEY_Q:           //养动物
        {
            AddAnimal();
            break;
        }
        case EventKeyboard::KeyCode::KEY_1:          //延伸键
        {
            if (lastKeycode == EventKeyboard::KeyCode::KEY_P)  //按了P以后
            {
                AddPlant("monster.png");
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_2:
        {
            if (lastKeycode == EventKeyboard::KeyCode::KEY_P)  //按了P以后
            {
                AddPlant("player.png");
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_E:                    //施法键
        {
            if (!IsBag && IsCollide)
            {
                if (collidedSprite)
                {
                    switch (collidedSprite->getType())
                    {
                        case Object::ObjectType::Animal:
                        {
                            collidedSprite->removeFromParent();
                            collidedSprite = nullptr;
                            break;
                        }
                        case Object::ObjectType::Plant:
                        {
                            auto plant = (Plant*)collidedSprite;
                            switch(plant->getState())
                            {
                                case Plant::State::Growth:
                                {
                                    plant->setState(Plant::State::None);
                                    collidedSprite->removeFromParent();
                                    collidedSprite = nullptr;
                                    break;
                                }
                                case Plant::State::Planted:
                                {
                                    plant->setState(Plant::State::Growth);
                                    plant->setTexture("player.png");
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            break;
        }
        default:
            break;
    }
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {

            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoUp));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
        {
            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoDown));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {

            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoLeft));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {


            auto repeat = this->hero->getActionByTag(static_cast<int>(MyActionTag::MyGoRight));
            if (repeat)
                this->hero->stopAction(repeat);
            break;
        }
        default:
            break;
    }
}

bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
    auto ShapeA = contact.getShapeA()->getBody();
    auto ShapeB = contact.getShapeB()->getBody();
    switch (ShapeB->getCategoryBitmask())
    {
        case (int)PhysicsCategory::Animal:
        {
            IsCollide = true;
            collidedSprite = (Object*)ShapeB->getNode();
            collidedSprite->setType(Object::ObjectType::Animal);
            break;
        }
        case (int)PhysicsCategory::Plant:
        {
            IsCollide = true;
            collidedSprite = (Object*)ShapeB->getNode();
            collidedSprite->setType(Object::ObjectType::Plant);
            break;
        }
        break;
    }
    return true;
}

bool HelloWorld::onContactSeparate(PhysicsContact& contact)
{
    auto ShapeA = contact.getShapeA()->getBody();
    auto ShapeB = contact.getShapeB()->getBody();
    switch (ShapeB->getCategoryBitmask())
    {
        case (int)PhysicsCategory::Animal:
        case (int)PhysicsCategory::Plant:
        {
            IsCollide = false;
            collidedSprite = nullptr;
            break;
        }
        default:
            break;
    }
    return true;
}
//种植植物
void HelloWorld::AddPlant(const std::string & filepath)
{
    auto position = hero->getPosition();
    auto plant = Plant::create(filepath);
    plant->setPosition(position);

    //添加物理体
    auto plantbody = PhysicsBody::createBox(plant->getContentSize());

    plantbody->setCategoryBitmask((int)PhysicsCategory::Plant);
    plantbody->setContactTestBitmask((int)PhysicsCategory::Hero);

    plant->setPhysicsBody(plantbody);

    this->addChild(plant, 2);
    plant->IsPlanted();
    plant->scheduleUpdate();
}

void HelloWorld::AddAnimal()
{
    //auto visblieSize = Director::getInstance()->getVisibleSize();
    //auto origin = Director::getInstance()->getVisibleOrigin();


    auto animal = Object::create("monster.png");
    animal->setPosition(hero->getPosition());
    auto animalbody = PhysicsBody::createBox(animal->getContentSize());

    animalbody->setGravityEnable(false);
    animalbody->setDynamic(false);
    animalbody->setCategoryBitmask((int)PhysicsCategory::Animal);
    animalbody->setContactTestBitmask((int)PhysicsCategory::Hero);

    animal->setPhysicsBody(animalbody);

    this->addChild(animal, 3);


    //auto sequence = Sequence::create(MoveBy::create(10.0f, Vec2(-500, 0)),MoveBy::create(10.0f,Vec2(500,0)), nullptr);
    //auto reAction = RepeatForever::create(sequence);
    //animal->runAction(reAction);
}




