#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"NPC.h"
#include"Plant.h"
class HelloWorld : public cocos2d::Layer
{
public:
    enum class FaceDirection
    {
        Up,
        Down,
        Left,
        Right,
        None
    };


    //创建场景函数
    static cocos2d::Scene* createScene();

    //初始化函数
    virtual bool init();

    // a selector callback

    virtual void update(float delta);              //重写的更新函数

    //键盘监听函数
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //碰撞函数
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual bool onContactSeparate(cocos2d::PhysicsContact& contact);

    //换季函数
    void ChangeSeason(float delta);              
    virtual void onExit();                  
    
    Plant* AddPlant(const std::string& filepath);                               //添加植物
    Object* AddAnimal(const std::string& filepath);                              //添加动物
  

    //Hero的方法
    void MoveHero(FaceDirection);                //Hero移动
    void initHero(const cocos2d::Vec2& pos);

    //Object层
    void initObject(const std::string& objectlayer,const std::string& objectname,int Category);

    //屏幕边缘检测
    void CheckEdge();

    //生成HelloWorld::create()
    CREATE_FUNC(HelloWorld);
protected:
    //瓦片地图成员,以瓦片地图为成员，方便切换季节
    cocos2d::TMXTiledMap* map = nullptr;               
   
    //主角
    cocos2d::Sprite* hero = nullptr;

    //被碰撞的物体
    Object* collidedSprite = nullptr;

    //是否碰撞检测
    bool IsCollide = false;

    //钓鱼检测
    bool IsFishing = false;

    //背包检测
    bool IsBag = false;

    //对话检测
    bool IsTalking = false;

    FaceDirection _direction = FaceDirection::None;
    
    FaceDirection _collidedir = FaceDirection::None;

    cocos2d::Vec2 _heroinitPos = {0,0};
};

#endif // __HELLOWORLD_SCENE_H__