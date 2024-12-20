/*
* 主场景函数
* 作用：农村场景函数，作为其他场景的中转以及种植养殖的所在地
*/
#include "HelloWorldScene.h"
#include"hero.h"
#include"OtherScene.h"
#include"NPC.h"
#include"menu.h"
#include"Plant.h"
#include"bag.h"
#include"animation.h"
#include"Item.h"
#include"TalkingScene.h"
USING_NS_CC;

Vec2 HERO_POSITION = { 0 , 0 };
const Size AnimalSize = { 60,60 };  //设置动物大小


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
    this->scheduleUpdate();
    this->schedule(SEL_SCHEDULE(&HelloWorld::ChangeSeason),10.0f,kRepeatForever,0.0f);
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    //设置图块层
    initMap("home map/home (2).tmx");
   
    initObject("Fish", "Fish",(int)PhysicsCategory::FishPoint);
    initObject("House", "House", (int)PhysicsCategory::Obstacle);
    initObject("Obstacle", "Canal",(int)PhysicsCategory::Obstacle);
    initObjects("Obstacle", "Handrail", (int)PhysicsCategory::Obstacle,7);
    initObjects("Obstacle", "Tree", (int)PhysicsCategory::Obstacle, 4);
    initObject("Home", "Home", (int)PhysicsCategory::Home);
    //加载地图
    

    //初始化英雄
    _heroinitPos = { visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y };
    initHero(_heroinitPos);

    //键盘监听
    addListener();

    //碰撞检测
    addContact();

    return true;
}

//场景帧更新函数
void HelloWorld::update(float delta)   
{
    auto director = Director::getInstance();
   
    auto ymax = Director::getInstance()->getVisibleSize().height;  //屏幕边缘
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = this->hero->getPosition();
    //屏幕边缘检测
    {
        CheckEdge();
    }
    if(abs(heroposition.x - xmax) < 10.0f && abs(heroposition.y - ymax / 2) < 100.0f)
    {
        HERO_POSITION = hero->getPosition();
        hero->setPosition(heroposition.x - 100.0f, heroposition.y);
        auto city = City::createScene();//下一个场景
        Director::getInstance()->pushScene(city);
        hero->stopAllActions();
    }
}
//换季函数
void HelloWorld::ChangeSeason(float delta)
{
    static int Time = 0;
    Time++;
    if(Time % 3 == 1)
    {
        Season("home map/home (2).tmx");
    }
    else if (Time % 3 == 2)
    {
        Season("map/farm_autumn.tmx");
    }
}
//
void HelloWorld::onExit()
{
    Layer::onExit();
}
//键盘响应函数
void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    static int BagNumber = 0;         //当BagNumber为奇数时，进入背包，当BagNumber为偶数时，离开背包
    static EventKeyboard::KeyCode lastKeycode = EventKeyboard::KeyCode::KEY_0;
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:   //主角向上移动
        {
             MoveHero(FaceDirection::Up);
            _direction = FaceDirection::Up;
        
            break;
        }
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW: //主角向下移动
        case EventKeyboard::KeyCode::KEY_S:
        {
            MoveHero(FaceDirection::Down);
            _direction = FaceDirection::Down;
            break;
        }
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: //主角向左移动
        {
            MoveHero(FaceDirection::Left);
            _direction = FaceDirection::Left;
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //主角向右移动
        {
            MoveHero(FaceDirection::Right);
            _direction = FaceDirection::Right;
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
            if (BagNumber & 1)                         //离开背包
            {
                auto bag = this->getChildByTag(Bag::BagTag);
               
                this->removeChildByTag(Bag::BagTag,true);
                IsBag = false;
            }
            else                                       //进入背包
            {
                auto bag = Bag::createLayer();
                bag->setTag(Bag::BagTag);
                this->addChild(bag, INT_MAX);
                IsBag = true;
            }
            BagNumber++;
            break;
        }
        case EventKeyboard::KeyCode::KEY_Q:           //养动物，演示用，正式版本不会设置专门产生动物的按键
        {
            lastKeycode = keyCode;
            break;
        }
        case EventKeyboard::KeyCode::KEY_1:          //延伸键
        {
            if (lastKeycode == EventKeyboard::KeyCode::KEY_P)  //按了P以后
            {
                auto plant = AddPlant("monster.png");
                plant->setType(Object::ObjectType::Plant);
            }
            if (lastKeycode == EventKeyboard::KeyCode::KEY_Q)
            {
                auto animal = AddAnimal("Animal/Sheep-turntorwards.png");
                animal->setType(Object::ObjectType::Sheep);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_2:
        {
            if (lastKeycode == EventKeyboard::KeyCode::KEY_P)  //按了P以后
            {
                auto plant = AddPlant("player.png");
                plant->setType(Object::ObjectType::Plant);
            }
            if (lastKeycode == EventKeyboard::KeyCode::KEY_Q)
            {
                auto animal = AddAnimal("player.png");
                animal->setType(Object::ObjectType::Chicken);
            }
            break;
        }
        case EventKeyboard::KeyCode::KEY_E:                    //施法键
        {
            if (!IsBag && IsCollide)
            {

                switch(_direction)
                {
                    case FaceDirection::Left:
                    {
                        auto animationaction = getanimation("qilunuo", "work", "left", 2, 0.1);
                        hero->runAction(animationaction);
                    }
                    break;
                    case FaceDirection::Down:
                    {
                        auto animationaction = getanimation("qilunuo", "work", "down", 2, 0.1);
                        hero->runAction(animationaction);
                    }
                    break;
                    case FaceDirection::Right:
                    {
                        auto animationaction = getanimation("qilunuo", "work", "right", 2, 0.1);
                        hero->runAction(animationaction);
                    }
                    break;
                    case FaceDirection::Up:
                    {
                        auto animationaction = getanimation("qilunuo", "work", "up", 2, 0.1);
                        hero->runAction(animationaction);
                    }
                    break;
                    default:
                        break;
                }

                if (collidedSprite)
                {

                    switch (collidedSprite->getType())
                    {
                        case Object::ObjectType::Sheep:   //杀羊
                        {
                            collidedSprite->removeFromParent();
                            collidedSprite = nullptr;
                            ItemVec::AddItem(ItemType::Sheep);
                            break;
                        }
                        case Object::ObjectType::Chicken: //杀鸡
                        {
                            collidedSprite->removeFromParent();
                            collidedSprite = nullptr;
                            ItemVec::AddItem(ItemType::Chicken);
                            break;
                        }
                        case Object::ObjectType::Plant:  //采植物或者催熟植物
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
                else if (IsFishing)
                {
                    std::random_device rd;
                    unsigned int seed = rd();

                    // 使用 std::mt19937 生成随机数
                    std::mt19937 generator(seed);

                    // 生成一个随机数
                    std::uniform_int_distribution<int> distribution(1, FishingProMaxPoint); // 生成 1 到 100 之间的随机数
                    int randomNumber = distribution(generator);
                    if (randomNumber == 1)
                    {
                        auto label = Label::createWithTTF("Success", "fonts/Marker Felt.ttf", 50);
                        label->setPosition(hero->getPositionX(), hero->getPositionY() + 50);
                        ItemVec::AddItem(ItemType::Fish);

                        auto delay = DelayTime::create(.5f); // 延迟 1 秒
                        auto remove = RemoveSelf::create();   // 移除自身
                        auto sequence = Sequence::create(delay, remove, nullptr);

                        // 将动作序列应用到 Label 上
                        label->runAction(sequence);
                        this->addChild(label, 3);
                    }
                    else
                    {
                        auto label = Label::createWithTTF("Fail", "fonts/Marker Felt.ttf", 50);
                        label->setPosition(hero->getPositionX(), hero->getPositionY() + 50);

                        auto delay = DelayTime::create(.5f); // 延迟 1 秒
                        auto remove = RemoveSelf::create();   // 移除自身
                        auto sequence = Sequence::create(delay, remove, nullptr);

                        // 将动作序列应用到 Label 上
                        label->runAction(sequence);
                        this->addChild(label, 3);
                    }
                }
            }
            break;
            case EventKeyboard::KeyCode::KEY_T:
            {
                if(IsTalking)
                {
                    auto npc = (NPC*)collidedSprite;
                    auto talking = TalkingScene::create();
                    switch (npc->getNPCName())
                    {
                        case NPC::NPCName::L:
                        {
                            
                            break;
                        }
                        case NPC::NPCName::M:
                        {
                            break;
                        }
                    }
                    this->addChild(talking, INT_MAX);
                }
            }
            break;
        }
        default:
            break;
    }
}
//键盘松开的响应函数
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


//碰撞函数
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
    auto ShapeA = contact.getShapeA()->getBody();
    auto ShapeB = contact.getShapeB()->getBody();
    ShapeA->getNode()->stopAllActions();

    //阻止深入
    switch (_direction)
    {
        case FaceDirection::Up:
            _collidedir = FaceDirection::Up;
            break;
        case FaceDirection::Down:
            _collidedir = FaceDirection::Down;
            break;
        case FaceDirection::Left:
            _collidedir = FaceDirection::Left;
            break;
        case FaceDirection::Right:
            _collidedir = FaceDirection::Right;
            break;
    }
    IsCollide = true;
    switch (ShapeB->getCategoryBitmask())
    {
        case (int)PhysicsCategory::Animal:
        {
            collidedSprite = (Object*)ShapeB->getNode();
            break;
        }
        case (int)PhysicsCategory::Plant:
        {
            collidedSprite = (Object*)ShapeB->getNode();
            break;
        }
        case (int)PhysicsCategory::FishPoint:
        {
            IsFishing = true;
            collidedSprite = nullptr;
            break;
        }
        case (int)PhysicsCategory::NPC:
        {
            IsTalking = true;
            collidedSprite = (Object*)ShapeB->getNode();
            break;
        }
        case (int)PhysicsCategory::Obstacle:
        {
            break;
        }
        case (int)PhysicsCategory::Home:
        {
            ChangeToHome();
            hero->setPosition(HERO_POSITION.x, HERO_POSITION.y - 50);
            IsCollide = false;
        }
        default:
            break;
    }
    return true;
}
//碰撞体分离函数
bool HelloWorld::onContactSeparate(PhysicsContact& contact)
{
    auto ShapeA = contact.getShapeA()->getBody();
    auto ShapeB = contact.getShapeB()->getBody();
    IsCollide = false;
    switch (ShapeB->getCategoryBitmask())
    {
        case (int)PhysicsCategory::Animal:
        case (int)PhysicsCategory::Plant:
        {
            collidedSprite = nullptr;
            break;
        }
        case (int)PhysicsCategory::FishPoint:
        {
            IsFishing = false;
            break;
        }
        case (int)PhysicsCategory::NPC:
        {
            IsTalking = false;
        }
        default:
            break;
    }
    return true;
}
//种植植物
Plant* HelloWorld::AddPlant(const std::string & filepath)
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
    return plant;
}
//添加动物
Object* HelloWorld::AddAnimal(const std::string& filepath)
{
    //auto visblieSize = Director::getInstance()->getVisibleSize();
    //auto origin = Director::getInstance()->getVisibleOrigin();

    auto animal = Object::create(filepath);
    animal->setPosition(hero->getPosition());
    //animal->setContentSize(AnimalSize);
    auto animalbody = PhysicsBody::createBox(animal->getContentSize());
    animalbody->setGravityEnable(false);
    animalbody->setDynamic(false);
    animalbody->setCategoryBitmask((int)PhysicsCategory::Animal);
    animalbody->setContactTestBitmask((int)PhysicsCategory::Hero);

    animal->setPhysicsBody(animalbody);

    this->addChild(animal, 3);

    return animal;
}

void HelloWorld::MoveHero(FaceDirection direction)
{
    if (IsBag)
        return;

   

    RepeatForever* repeat = nullptr;
    Animate* animationaction = nullptr;
    MoveBy* action = nullptr;
    switch (direction)
    {
        case FaceDirection::Up:
        {
            if (IsCollide && _collidedir == FaceDirection::Up)
                break;
            _direction = FaceDirection::Up;
            action = MoveBy::create(0.4f, Vec2(0, 4 * HERO_SPEED));
            animationaction = getanimation("qilunuo", "walk", "up", 4, 0.1);
            repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
            repeat->setTag(static_cast<int>(MyActionTag::MyGoUp));
        }
        break;
        case FaceDirection::Down:
        {
            if (IsCollide && _collidedir == FaceDirection::Down)
                break;
            _direction = FaceDirection::Down;
            action = MoveBy::create(0.4f, Vec2(0, -4 * HERO_SPEED));
            animationaction = getanimation("qilunuo", "walk", "down", 4, 0.1);
            repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
            repeat->setTag(static_cast<int>(MyActionTag::MyGoDown));
        }
        break;
        case FaceDirection::Right:
        {
            if (IsCollide && _collidedir == FaceDirection::Right)
                break;
            _direction = FaceDirection::Right;
            action = MoveBy::create(0.4f, Vec2(4 * HERO_SPEED, 0));
            animationaction = getanimation("qilunuo", "walk", "right", 4, 0.1);
            repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
            repeat->setTag(static_cast<int>(MyActionTag::MyGoRight));
        }
        break;
        case FaceDirection::Left:
        {
            if (IsCollide && _collidedir == FaceDirection::Left)
                break;
            _direction = FaceDirection::Left;
            action = MoveBy::create(0.4f, Vec2(-4 * HERO_SPEED, 0));
            animationaction = getanimation("qilunuo", "walk", "left", 4, 0.1);
            repeat = RepeatForever::create(Spawn::create(action, animationaction, nullptr));
            repeat->setTag(static_cast<int>(MyActionTag::MyGoLeft));
        }
        break;
        default:
            break;
    }
    if(repeat)
        hero->runAction(repeat);
    return;
}

void HelloWorld::initObject(const std::string & objectlayer,const std::string& objectname,int Category)
{
    //设置图块层
    auto maplayer = map->getObjectGroup(objectlayer);
    auto mapobject = maplayer->getObject(objectname);
    //获取对象的属性
    float x = mapobject["x"].asFloat();
    float y = mapobject["y"].asFloat();
    float width = mapobject["width"].asFloat();
    float height = mapobject["height"].asFloat();
        //设置物理体
    auto body = PhysicsBody::createBox(Size(width, height));
    body->setDynamic(false); // 设置为静态物体
    body->setCategoryBitmask(Category);
    body->setContactTestBitmask((int)PhysicsCategory::Hero);
    auto node = Node::create();
    node->setPosition(mapobject["x"].asFloat() + width / 2, y + height / 2); // 设置节点的位置（中心对齐）
    node->setPhysicsBody(body);
    this->addChild(node, 1);
}

//初始化主角
void HelloWorld::initHero(const Vec2& pos)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    hero = initframe("qilunuo", "walk", "down");
    hero->setPosition(pos);
    this->addChild(hero, 3);
    auto herobody = PhysicsBody::createBox(Size(hero->getContentSize().width / 2 , hero->getContentSize().height / 3));
    herobody->setPositionOffset(Vec2(0, -hero->getContentSize().height * 0.25f));
    herobody->setGravityEnable(false);
    herobody->setDynamic(false);

    //设置位掩码
    herobody->setCategoryBitmask((int)PhysicsCategory::Hero);
    herobody->setContactTestBitmask(0xfffffff);
    herobody->setCollisionBitmask(0);
    hero->setPhysicsBody(herobody);
    hero->stopAllActions();
}

void HelloWorld::CheckEdge()
{
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
}

void HelloWorld::addListener()
{
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
}

void HelloWorld::addContact()
{
    auto physicalcontact = cocos2d::EventListenerPhysicsContact::create();
    physicalcontact->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    physicalcontact->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(physicalcontact, this);
}

void HelloWorld::initMap(const std::string& mapfile)
{
    //初始地图
    if (!map)
        map = TMXTiledMap::create(mapfile);                  //加载瓦片地图,初始地图 

    auto director = Director::getInstance();                       //获得导演
    map->setScale(director->getVisibleSize().width / map->getContentSize().width);              //调整大小，适配屏幕
    map->setAnchorPoint(Vec2(0, 0));
    this->addChild(map, 1);
}

void HelloWorld::initObjects(const std::string& objectlayer, const std::string& objectname, int Category,int maxnumber)
{
    for (int i = 1; i <= maxnumber; i++)
    {
        initObject(objectlayer, objectname + std::to_string(i), (int)PhysicsCategory::Obstacle);
    }
}

void HelloWorld::Season(const std::string& filepath)
{
    auto zorder = map->getLocalZOrder();
    auto newmap = TMXTiledMap::create(filepath);
    auto director = Director::getInstance();                       //获得导演
    newmap->setScale(director->getVisibleSize().width / newmap->getContentSize().width);              //调整大小，适配屏幕
    this->removeChild(map, true);
    this->addChild(newmap, zorder);
    map = newmap;
}

void HelloWorld::ChangeToHome()
{
    auto ymax = Director::getInstance()->getVisibleSize().height;  //屏幕边缘
    auto xmax = Director::getInstance()->getVisibleSize().width;
    auto heroposition = this->hero->getPosition();
    HERO_POSITION = hero->getPosition();
   
    auto home = Home::createScene();//下一个场景
    Director::getInstance()->pushScene(home);
    hero->stopAllActions();
}