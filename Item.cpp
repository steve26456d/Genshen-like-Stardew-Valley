#include"Item.h"

USING_NS_CC;

std::vector<ItemType> ItemVec::_vec;
std::set<ItemType> ItemVec::_set;

//在命名空间ItemNumber中记录每一种物品的数量
int ItemNumber::Chicken = 0;
int ItemNumber::Dish = 0;
int ItemNumber::Fish = 0;
int ItemNumber::Mineral = 0;
int ItemNumber::Money = 0;
int ItemNumber::Sheep = 0;


//在ItemVec中添加Item
bool ItemVec::AddItem(const ItemType& itemType)
{

	if (_set.count(itemType) <= 0)
	{
		//该物品不存在
		_vec.push_back(itemType);
		_set.insert(itemType);
		switch (itemType)
		{
			case ItemType::Chicken:
				ItemNumber::Chicken++;
				break;
			case ItemType::Dish:
				ItemNumber::Dish++;
				break;
			case ItemType::Fish:
				ItemNumber::Fish++;
				break;
			case ItemType::Mineral:
				ItemNumber::Mineral++;
				break;
			case ItemType::Sheep:
				ItemNumber::Sheep++;
				break;
		}
	}
	else
	{
		switch (itemType)
		{
			case ItemType::Chicken:
				ItemNumber::Chicken++;
				break;
			case ItemType::Dish:
				ItemNumber::Dish++;
				break;
			case ItemType::Fish:
				ItemNumber::Fish++;
				break;
			case ItemType::Mineral:
				ItemNumber::Mineral++;
				break;
			case ItemType::Sheep:
				ItemNumber::Sheep++;
				break;
		}
	}
	return true;
}

//删除某个物品特定数量
bool ItemVec::removeItem(ItemType itemtype, int number)
{

	if (_set.count(itemtype) <= 0)
	{
		//该物品不存在
		return false;
	}
	else
	{
		switch (itemtype)
		{
			case ItemType::Chicken:
			{
				if (ItemNumber::Chicken > number)
				{
					ItemNumber::Chicken -= number;
					if (ItemNumber::Chicken <= 0)
					{
						_vec.erase(std::remove(_vec.begin(), _vec.end(), itemtype),_vec.end());
						_set.erase(itemtype);
					}
				}
				else
					return false;
			}
				break;
			case ItemType::Dish:
			{
				if (ItemNumber::Dish > number)
				{
					ItemNumber::Dish -= number;
					if (ItemNumber::Dish <= 0)
					{
						_vec.erase(std::remove(_vec.begin(), _vec.end(), itemtype), _vec.end());
						_set.erase(itemtype);
					}
				}
				else
					return false;
			}
				break;
			case ItemType::Fish:
			{
				if (ItemNumber::Fish > number)
				{
					ItemNumber::Fish -= number;
					if (ItemNumber::Fish <= 0)
					{
						_vec.erase(std::remove(_vec.begin(), _vec.end(), itemtype), _vec.end());
						_set.erase(itemtype);
					}
				}
				else
					return false;
			}
				break;
			case ItemType::Mineral:
			{
				if (ItemNumber::Mineral > number)
				{
					ItemNumber::Mineral -= number;
					if (ItemNumber::Mineral <= 0)
					{
						_vec.erase(std::remove(_vec.begin(), _vec.end(), itemtype), _vec.end());
						_set.erase(itemtype);
					}
				}
				else
					return false;
			}
				break;
			case ItemType::Sheep:
			{
				if (ItemNumber::Sheep > number)
				{
					ItemNumber::Sheep -= number;
					if (ItemNumber::Sheep <= 0)
					{
						_vec.erase(std::remove(_vec.begin(), _vec.end(), itemtype), _vec.end());
						_set.erase(itemtype);
					}
				}
				else
					return false;
			}
				break;
			default:
				break;
		}
	}
	return true;
}

//寻找ItemVec中的Item
