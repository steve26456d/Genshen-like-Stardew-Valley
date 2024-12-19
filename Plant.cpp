#include"Plant.h"
USING_NS_CC;

float Plant::_todeathtime = 120.0f;

Plant* Plant::create(const std::string& filename)
{
	Plant* plant = new Plant;
	if (plant->init(filename))
	{
		plant->autorelease();
	}
	else
	{
		delete plant;
		plant = nullptr;
		return nullptr;
	}
	return plant;
}

bool Plant::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename))
		return false;

	this->scheduleUpdate();
	_plantstate = State::None;
	return true;
}
//植物的场景帧更新函数，是植物死亡倒计时
void Plant::update(float delta)
{
	if(_plantstate == State::Planted)
	{
		_deathtime += 1;
		if(_deathtime > _todeathtime)
			this->removeFromParent();
	}
}
//植物种植函数，当植物被种下后，调用此函数，植物状态被设置为已种植
void Plant::IsPlanted()
{
	if(_plantstate == State::None)
	    _plantstate = State::Planted;
}
//回调死亡时间
void Plant::ResetDeathtime()
{
	_deathtime = 0;
}

//设置植物状态的函数
void Plant::setState(State state)
{
	_plantstate = state;
}
//获取植物状态的函数
Plant::State Plant::getState()
{
	return _plantstate;
}