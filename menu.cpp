#include<cocos2d.h>
#include"menu.h"
#include<sstream>
USING_NS_CC;
namespace GlobalV        //技能树等级以及种类
{
	int SkillPoint = 100;
	int farm_level = 0;
	int mine_level = 0;
	int fish_level = 0;
	int cook_level = 0;
}
Scene* GameMenu::createScene()
{
	return GameMenu::create();
}
	
bool GameMenu::init()
{
	if (!Scene::init())
		return false;
	this->setColor(Color3B::WHITE);
	auto director = Director::getInstance();
	auto visSize = director->getVisibleSize();
	auto Origin = director->getVisibleOrigin();

	std::stringstream skillstring;
	skillstring << "Skill Point:  " << GlobalV::SkillPoint << "   (if you want to upgrade your skill , press cltr + number)" << std::endl;
	AddLabel(label_skill, skillstring.str(), Vec2(visSize.width / 2 + Origin.x, visSize.height / 6 * 5 + Origin.y), 60);

	std::stringstream string_farm;
	string_farm << "1.farm Level:     " << GlobalV::farm_level << std::endl;
	label_farm = Label::createWithTTF(string_farm.str(), "fonts/Marker Felt.ttf", 100);
	label_farm->setColor(Color3B::WHITE);
	label_farm->enableOutline(Color4B::RED,4);
	label_farm->setPosition(Vec2(visSize.width / 2 + Origin.x ,  visSize.height / 6 * 4 + Origin.y));
	this->addChild(label_farm, 2);

	std::stringstream string_cook;
	string_cook << "2.Cook Level:     " << GlobalV::cook_level << std::endl;
	AddLabel(label_cook, string_cook.str(), Vec2(visSize.width / 2 + Origin.x, visSize.height / 6 * 3 + Origin.y), 100);

	std::stringstream string_mine;
	string_mine << "3.Mine Level:     " << GlobalV::mine_level << std::endl;
	AddLabel(label_mine, string_mine.str(), Vec2(visSize.width / 2 + Origin.x, visSize.height / 6 * 2 + Origin.y), 100);

	std::stringstream string_fish;
	string_fish << "4.Fish Level:     " << GlobalV::fish_level << std::endl;
	AddLabel(label_fish, string_fish.str(), Vec2(visSize.width / 2 + Origin.x, visSize.height / 6 + Origin.y), 100);


	auto listenkeyboard = EventListenerKeyboard::create();
	listenkeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode,Event* event)
		{
			switch (keycode)
			{
				case EventKeyboard::KeyCode::KEY_1:
				{
					if (GlobalV::SkillPoint > 0)
					{
						GlobalV::SkillPoint--;
						GlobalV::farm_level++;
						std::stringstream string_farm;
						string_farm << "1.farm Level:     " << GlobalV::farm_level << std::endl;;
						auto new_label  = Label::createWithTTF(string_farm.str(),"fonts/Marker Felt.ttf",100);
						new_label->setTextColor(label_farm->getTextColor());
						new_label->enableOutline(Color4B::RED,label_farm->getOutlineSize());
						new_label->enableShadow();
						new_label->setPosition(label_farm->getPosition());
						this->addChild(new_label, label_farm->getLocalZOrder());
						label_farm->removeFromParent();
						label_farm = new_label;

						Label* new_skill_label;
						std::stringstream skillstring;
						skillstring << "Skill Point:  " << GlobalV::SkillPoint << "   (if you want to upgrade your skill , press Cltr + Number)" << std::endl;
						AddLabel(new_skill_label, skillstring.str(),label_skill->getPosition(), 60);
						label_skill->removeFromParent();
						label_skill = new_skill_label;
					}
					break;
				}
				case EventKeyboard::KeyCode::KEY_2:
				{
					if (GlobalV::SkillPoint > 0)
					{
						GlobalV::SkillPoint--;
						GlobalV::cook_level++;
						
						std::stringstream string_cook;
						Label* new_cook_label;
						string_cook << "2.Cook Level:     " << GlobalV::cook_level << std::endl;
						AddLabel(new_cook_label, string_cook.str(), label_cook->getPosition(), 100);
						label_cook->removeFromParent();
						label_cook = new_cook_label;

						Label* new_skill_label;
						std::stringstream skillstring;
						skillstring << "Skill Point:  " << GlobalV::SkillPoint << "   (if you want to upgrade your skill , press Cltr + Number)" << std::endl;
						AddLabel(new_skill_label, skillstring.str(), label_skill->getPosition(), 60);
						label_skill->removeFromParent();
						label_skill = new_skill_label;
					}
					break;
				}
				case EventKeyboard::KeyCode::KEY_3:
				{
					if (GlobalV::SkillPoint > 0)
					{
						GlobalV::SkillPoint--;
						GlobalV::mine_level++;

						std::stringstream string_mine;
						Label* new_mine_label;
						string_mine << "3.Mine Level:     " << GlobalV::mine_level << std::endl;
						AddLabel(new_mine_label, string_mine.str(), label_mine->getPosition(), 100);
						label_mine->removeFromParent();
						label_mine = new_mine_label;

						Label* new_skill_label;
						std::stringstream skillstring;
						skillstring << "Skill Point:  " << GlobalV::SkillPoint << "   (if you want to upgrade your skill , press Cltr + Number)" << std::endl;
						AddLabel(new_skill_label, skillstring.str(), label_skill->getPosition(), 60);
						label_skill->removeFromParent();
						label_skill = new_skill_label;
					}
					break;
				}
				case EventKeyboard::KeyCode::KEY_4:
				{
					if (GlobalV::SkillPoint > 0)
					{
						GlobalV::SkillPoint--;
						GlobalV::fish_level++;

						std::stringstream string_fish;
						Label* new_fish_label;
						string_fish << "4.Fish Level:     " << GlobalV::fish_level << std::endl;
						AddLabel(new_fish_label, string_fish.str(), label_fish->getPosition(), 100);
						label_fish->removeFromParent();
						label_fish = new_fish_label;

						Label* new_skill_label;
						std::stringstream skillstring;
						skillstring << "Skill Point:  " << GlobalV::SkillPoint << "   (if you want to upgrade your skill , press Cltr + Number)" << std::endl;
						AddLabel(new_skill_label, skillstring.str(), label_skill->getPosition(), 60);
						label_skill->removeFromParent();
						label_skill = new_skill_label;
						//出货概率
						if (FishingProMaxPoint > 2)
							FishingProMaxPoint--;
					}
					break;
				}
				case EventKeyboard::KeyCode::KEY_ESCAPE:
				{
					Director::getInstance()->popScene();
					break;
				}
				default:
					break;
			}
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenkeyboard, this);
	return true;
}


void GameMenu::AddLabel(cocos2d::Label*& label,std::string str,Vec2 location , float FontSize)
{
	label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", FontSize);
	label->setColor(Color3B::WHITE);
	label->enableOutline(Color4B::RED,4);
	label->setPosition(location);
	this->addChild(label, 2);
}