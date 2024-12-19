/*
* 背包函数的具体实现
*/

#include"Bag.h"
#include<cocos2d.h>
#include<vector>
USING_NS_CC;

float Bag::BeginX = 0;
float Bag::EndX = 0;
float Bag::BeginY = 0;
float Bag::EndY = 0;
int Bag::BagTag = 111;

int BagLine = 10;

Layer* Bag::createLayer()
{
	return Bag::create();
}

bool Bag::init()
{
	if (!Layer::init())
		return false;
	auto director = Director::getInstance();
	auto origin = director->getVisibleOrigin();
	auto viSize = director->getVisibleSize();

	//加载初始选中的格子
    select_cell = Sprite::create("bag/Inventory_select.png");
	select_cell->setContentSize(select_cell->getContentSize() * 4);

	//初始化格子的边界
	BeginX = viSize.width / 2 - 5 * select_cell->getContentSize().width;
	EndX = viSize.width / 2 + 5 * select_cell->getContentSize().width;
	BeginY = viSize.height / 2 - 5 * select_cell->getContentSize().height;
	EndY = viSize.height / 2 + 5 * select_cell->getContentSize().height;

	//将初始的选中格子放入Layer中
	select_cell->setPosition(BeginX, BeginY);

	for (float X = BeginX; X <= EndX; X += select_cell->getContentSize().width)   //添加格子
		for(float Y = BeginY;Y <= EndY;Y += select_cell->getContentSize().height)
		    AddCell(Vec2(X, Y));
	
	this->addChild(select_cell,_bag_order);

	auto selectSize = select_cell->getContentSize();
	//加载存放的物品
	int turn = 0;
	for (size_t it = 0; it < ItemVec::_vec.size(); it++)
	{
		int itemCount = 0;
		Sprite* sprite;
		switch (ItemVec::_vec[it])
		{
			case ItemType::Chicken:
			{
				sprite = Sprite::create("object/Chicken.png");
				itemCount = ItemNumber::Chicken;
			}
			break;
			case ItemType::Dish:
			{
				itemCount = ItemNumber::Dish;
			}
				break;
			case ItemType::Fish:
			{
				sprite = Sprite::create("object/Fish.png");
				itemCount = ItemNumber::Fish;
			}
			break;
			case ItemType::Mineral:
			{
				sprite = Sprite::create("object/Mineral.png");
				itemCount = ItemNumber::Mineral;
			}
				break;
			case ItemType::Money:
				itemCount = ItemNumber::Money;
				break;
			case ItemType::Sheep:
			{
				sprite = Sprite::create("object/Sheep.png");
				itemCount = ItemNumber::Sheep;
			}
				break;
			default:
				break;
		}
		sprite->setPosition(BeginX + (turn % BagLine) * selectSize.width * 0.95, BeginY + (turn / BagLine) * selectSize.height * 0.95);
		sprite->setScale(selectSize.width / sprite->getContentSize().width - 0.05);
		this->addChild(sprite, _bag_order + 1);
		auto label = Label::createWithTTF(std::to_string(itemCount), "fonts/Marker Felt.ttf", 50);
		label->setTextColor(Color4B::BLACK);
		label->setPosition(sprite->getPosition());
		this->addChild(label, _bag_order + 1);
		turn++;
	}
	//创建背包的键盘响应

	auto bagKey = EventListenerKeyboard::create();

	bagKey->onKeyPressed = CC_CALLBACK_2(Bag::onKeyPressed, this);

	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(bagKey, this);
	return true;
}

void Bag::AddCell(Vec2 Pos)
{
	auto sprite = Sprite::create("bag/Inventory_Slot.png");
	sprite->setScale(4.0);
	sprite->setPosition(Pos);
	this->addChild(sprite, _bag_order);
}

void Bag::onKeyPressed(EventKeyboard::KeyCode keycode,Event* event)
{
	auto position = select_cell->getPosition();
	//移动选中的格子
	switch (keycode)
	{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			if (position.y >= EndY)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x, position.y + select_cell->getContentSize().height));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			if (position.y <= BeginY)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x, position.y - select_cell->getContentSize().height));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			if (position.x <= BeginX)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x - select_cell->getContentSize().width, position.y));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			if (position.x >= EndX)
				;
			else
			{
				auto moveto = MoveTo::create(1e-6, Vec2(position.x + select_cell->getContentSize().width, position.y));

				select_cell->runAction(moveto);
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_B:
		{
			break;
		}
		default:
			break;
	}
}