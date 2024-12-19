#pragma once

/*
* 名字：Item类
* 作用：存储在背包的物品以及存放Item的向量类
* 内容：继承自cocos2d::Sprite类，可以根据Item::ItemType枚举创建形象
*/

#ifndef _ITEM_H_
#define _ITEM_H_
#include<cocos2d.h>
#include<algorithm>
#include<vector>
class Bag;
class ItemVec;
//存储在背包的物品类

	enum class ItemType   //Item的种类
	{
		None,
		Chicken,
		Sheep,
		Fish,
		Mineral,
		Dish,
		Money
	};

class ItemVec
{
public:
	//添加物品
	static bool AddItem(const ItemType&);
	//删除物品
	static bool removeItem(ItemType,int);
	
	friend class Bag;
private:
	static std::vector<ItemType> _vec;  //顺序记录存放的物品
	static std::set<ItemType> _set;     //记录这个物品是否存在
	ItemVec(){}
};


//物品数量
namespace ItemNumber
{
	extern int Chicken;
	extern int Sheep;
	extern int Fish;
	extern int Mineral;
	extern int Dish;
	extern int Money;
};
#endif