#pragma once
#include<cocos2d.h>
/*
* 作用: 重写NPC
*/

//物理体掩码
enum class PhysicsCategory 
{
	None = 0,
	Hero = (1 << 0),
	NPC = (1 << 1),
	Animal = (1 << 2),
	Plant = (1 << 3),
	FishPoint = (1 << 4)
};
//作为所有NPC，动物，植物的父类，继承自Sprite类
class Object : public cocos2d::Sprite 
{
public:
	enum class ObjectType
	{
		Plant,
		Sheep,
		Chicken
	};
	static Object* create(const std::string& filepath);

	ObjectType getType();

	void setType(ObjectType type);
protected:
	ObjectType _type;
};

