#include<cocos2d.h>
#include"NPC.h"


Object::ObjectType Object::getType()
{
	return _type;
}

void Object::setType(ObjectType type)
{
	_type = type;
}

Object* Object::create(const std::string& filepath)
{
	Object* object = new (std::nothrow) Object;
	if (object && object->initWithFile(filepath))
	{
		object->autorelease();
		return object;
	}
	else
	{
		CC_SAFE_DELETE(object);
		return nullptr;
	}
}

NPC* NPC::create(const std::string& filename)
{
	NPC* npc = new (std::nothrow) NPC;
	if (npc && npc->initWithFile(filename))
	{
		npc->autorelease();
		return npc;
	}
	else
	{
		CC_SAFE_DELETE(npc);
		return nullptr;
	}
}

void NPC::setNPCName(const NPC::NPCName& name)
{
	_name = name;
}

NPC::NPCName NPC::getNPCName()
{
	return _name;
}