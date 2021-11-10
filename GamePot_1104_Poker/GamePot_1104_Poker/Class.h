#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Effect;
class Unit;
class Skill;
class Item;
class GameManager;

struct Stat
{

	int n_HP;
	int n_Energy;
	int n_AD;
	int n_AP;
	int n_AD_DEF;
	int n_AP_DEF;
	int n_CRIT;
	int n_CRITDMG = 2;
	int n_Drain;
	int n_Toughness;

	

	Stat(int _hp = 0, int _energy = 0, int _ad = 0, int _ap = 0, 
		int _ad_def = 0, int _ap_def = 0,int _crit = 0, int _drain = 0, int _toughness = 0)
	{
		n_HP = _hp;
		n_Energy = _energy;
		n_AD = _ad;
		n_AP = _ap;
		n_AD_DEF = _ad_def;
		n_AP_DEF = _ap_def;
		n_CRIT = _crit;
		n_Drain = _drain;
		n_Toughness = _toughness;
	}

	void operator+=(const int value)
	{
		this->n_HP += value;
		this->n_Energy += value;
		this->n_AD += value;
		this->n_AP += value;
		this->n_AD_DEF += value;
		this->n_AP_DEF += value;
		this->n_CRIT += value;
		this->n_CRITDMG += value;
		this->n_Drain += value;
		this->n_Toughness += value;
	}

	Stat operator+(const Stat& stat)
	{
		Stat sResult;
		sResult.n_HP = n_HP + stat.n_HP;
		sResult.n_Energy = n_Energy + stat.n_Energy;
		sResult.n_AD = n_AD + stat.n_AD;
		sResult.n_AP = n_AP + stat.n_AP;
		sResult.n_AD_DEF = n_AD_DEF + stat.n_AD_DEF;
		sResult.n_AP_DEF = n_AP_DEF + stat.n_AP_DEF;
		sResult.n_CRIT = n_CRIT + stat.n_CRIT;
		sResult.n_CRITDMG = n_CRITDMG + stat.n_CRITDMG;
		sResult.n_Drain = n_Drain + stat.n_Drain;
		sResult.n_Toughness = n_Toughness + stat.n_Toughness;
		return sResult;
	}

	Stat operator-(const Stat& stat)
	{
		Stat sResult;
		sResult.n_HP = n_HP - stat.n_HP;
		sResult.n_Energy = n_Energy - stat.n_Energy;
		sResult.n_AD = n_AD - stat.n_AD;
		sResult.n_AP = n_AP - stat.n_AP;
		sResult.n_AD_DEF = n_AD_DEF - stat.n_AD_DEF;
		sResult.n_AP_DEF = n_AP_DEF - stat.n_AP_DEF;
		sResult.n_CRIT = n_CRIT - stat.n_CRIT;
		sResult.n_CRITDMG = n_CRITDMG - stat.n_CRITDMG;
		sResult.n_Drain = n_Drain - stat.n_Drain;
		sResult.n_Toughness = n_Toughness - stat.n_Toughness;
		return sResult;
	}



	
};

class Unit
{
private:
	string m_Name;
	int m_UnitNumber; 
	int MaxHP;
	int MaxEnergy;
	// 52�����ؼ� �����̵�, ���̾�, ��Ʈ ,Ŭ�ι��� ǥ�� �߰������� �� �ڿ� ����
public:
	Stat UnitStatus;
	enum class E_STATUS_AILMENT { Slowdown, Silence, Faint, Aggro, Normal };
	E_STATUS_AILMENT m_Unit_Ailment;

	vector<Skill*> listSkill;

	vector<Item*> listItem;
public:
	Unit(){ }
	Unit(string name, int number, Stat status)
	{
		listSkill.resize(4);
		m_Unit_Ailment = E_STATUS_AILMENT::Normal;
		UnitStatus = status;
		m_UnitNumber = number;
		MaxHP = status.n_HP;
		MaxEnergy = status.n_Energy;
	}

	void SetItem(Item* item)
	{
		listItem.push_back(item);
	}

	Item* GetItem(int idx)
	{
		return listItem[idx];
	}

	void DeleteItem(int idx)
	{
		listItem.erase(listItem.begin() + idx);
	}

};


class UnitManager
{
public:
	vector<Unit> m_listFriendlyUnit;
	vector<Unit> m_listEnemyUnit;
	vector<Unit> m_listChosenFriendlyUnit;
	vector<Unit> m_listChosenEnenyUnit;

	UnitManager()
	{
		m_listFriendlyUnit.resize(4);
		m_listEnemyUnit.resize(4);
		// ������ 9�� ������Ŭ 0��° ������ 
		m_listFriendlyUnit[0] = Unit("�ٸ���", 0, Stat(100, 100, 100, 100, 100, 100, 100, 100, 100));
		m_listFriendlyUnit[1] = Unit("�����̵忡�̽�", 1, Stat(10, 5, 3, 0, 0, 0, 10, 0, 20));
		//�̷��� 52��

	}
	
};



class Effect
{
protected:
	
public:
	
	int m_percent = 100;
	void AddPercent(int percent)
	{
		m_percent = percent;
	}
	virtual void Use(Unit& caster, Unit& target) = 0;
	virtual string GetType() = 0;
};

// �� �ڿ� ȿ�� �߰�

class Heal : public Effect
{
	
public:
	void Use(Unit& caster, Unit& target)
	{
		target.UnitStatus.n_HP += caster.UnitStatus.n_AP * m_percent / 100;
	}

	string GetType()
	{
		string type = "ġ��";
		return type;
	}

};

class AD_Attack : public Effect
{
public:
	void Use(Unit& caster, Unit& target)
	{
		target.UnitStatus.n_HP -= caster.UnitStatus.n_AD * m_percent / 100;
	}

	string GetType()
	{
		string type = "��������";
		return type;
	}
};

class AP_Attack : public Effect
{
public:
	void Use(Unit& caster, Unit& target)
	{
		target.UnitStatus.n_HP -= caster.UnitStatus.n_AP * m_percent / 100;
	}

	string GetType()
	{
		string type = "��������";
		return type;
	}
};


class EffectManager
{
	vector<Effect*> listEffect;
public:
	void Init()
	{
		// ȿ�� �߰��� ���⿡ �ֽ�ȭ
		listEffect.resize(3);
		listEffect[0] = new Heal();
		listEffect[1] = new AD_Attack();
		listEffect[2] = new AP_Attack();

	}
	Effect* GetEffect(int idx)
	{
		return listEffect[idx];
	}
};

class Skill
{
	vector<Effect*> listEffect;
public:
	void AddEffect(Effect* effect)
	{
		listEffect.push_back(effect);
	}
	void Active(Unit& caster, Unit& target)
	{
		for (int i = 0; i < listEffect.size(); i++)
		{
			listEffect.at(i)->Use(caster, target);
		}
	}
};


class SkillManager
{
	vector<Skill*> listSkill;
public:

	void Init(EffectManager* pEffectManager)
	{
		// �� �ڿ� ��ų �߰�(ȿ���� ����) �� ���� �ֽ�ȭ
		listSkill.resize(3);
		listSkill[0] = new Skill();
		listSkill[0]->AddEffect(pEffectManager->GetEffect(0));
		listSkill[1] = new Skill();
		listSkill[1]->AddEffect(pEffectManager->GetEffect(1));
		listSkill[2] = new Skill();
		listSkill[2]->AddEffect(pEffectManager->GetEffect(2));
		listSkill[2]->AddEffect(pEffectManager->GetEffect(0));
	}
	Skill* GetSkill(int idx)
	{
		return listSkill[idx];
	}
};

class Map
{
	enum E_MAPTYPE { ItemShop, BattleField, Start, BossBattle, MAX};
	E_MAPTYPE e_MapType;
	vector<Unit> Enemy_in_Map;
	vector<Map> nearMap;
	int difficulty = 0;
public:
	bool is_clear = false;
	
	Map()
	{
		Enemy_in_Map.resize(4);
	}

	void PushEnemy(Unit enemy)
	{
		Enemy_in_Map.push_back(enemy);
	}
};

// �� �ڿ� �� �߰�


class MapManager
{
	vector<Map*> listMap;
	// ���������� �����
public:

	void Init(MapManager* pMapManager)
	{
		listMap.resize(4);
	}

	Map* GetMap(int idx)
	{
		return listMap[idx];
	}

};

class Item
{
	enum E_ITEM_KIND { ARCITACT, POTION, THROW };

	E_ITEM_KIND e_ItemKind;

	string strName;
	string strComment;
	Stat sFuction;
	int nGold;
	vector<Effect*> listSpecialEffect;
public:
	Item() {}
	Item(E_ITEM_KIND kind, string name, string comment, Stat status, int gold)
	{
		e_ItemKind = kind;
		strName = name;
		strComment = comment;
		sFuction = status;
		nGold = gold;
	}
	void AddEffect(Effect* effect)
	{
		listSpecialEffect.push_back(effect);
	}

	void Active(Unit& caster, Unit& target)
	{
		for (int i = 0; i < listSpecialEffect.size(); i++)
		{
			listSpecialEffect.at(i)->Use(caster, target);
		}
	}

	int GetGold()
	{
		return nGold;
	}
};

class ItemManager
{
	vector<Item> m_listItems;
public:
	void Init()
	{
		m_listItems.resize(10);

	}
	Item GetItem(int idx)
	{
		return m_listItems[idx];
	}
};

class Player
{
	int pGold = 0;
public:
	
	Map* pLocation_now;
	vector<Unit> listChosenUnit;
	vector<Item*> plistInventory;

	Player()
	{
		pLocation_now = NULL;
		listChosenUnit.resize(4);
		plistInventory.resize(5);
	}
	//////////////////// �κ��丮 ���� �Լ� /////////////////////////

	void SetInventory(Item* item)
	{
		plistInventory.push_back(item);
	}

	Item* GetInventory(int idx)
	{
		return plistInventory[idx];
	}

	void DeleteInventory(int idx)
	{
		plistInventory.erase(plistInventory.begin() + idx);
	}

	/////////////////// ���� ���� �Լ� /////////////////////////

	bool Buy(Item* item, int idx)
	{
		pGold -= item->GetGold();
		GetInventory(idx); 
		if (item->GetGold() <= pGold)
		{
			SetInventory(item);
			pGold -= item->GetGold();
			return true;
		}
		return false;
	}

	void Sell(int idx)
	{
		Item* item = GetInventory(idx);
		DeleteInventory(idx);
		pGold += item->GetGold();
	}

	/////////////////// ���� ���� �Լ� /////////////////////////

	void SetUnit(Unit unit)
	{
		listChosenUnit.push_back(unit);
	}

	Unit GetUnit(int idx)
	{
		return listChosenUnit[idx];
	}

	void DeleteUnit(int idx)
	{
		listChosenUnit.erase(listChosenUnit.begin() + idx);
	}

	bool Equip(int Unitidx, int Itemidx)
	{
		if (listChosenUnit[Unitidx].listItem.size() < 4)
		{
			listChosenUnit[Unitidx].listItem.push_back(plistInventory[Itemidx]);
			DeleteInventory(Itemidx);
			return true;
		}
		return false;
	}

	bool UnEquip(int Unitidx, int UnitItemidx, int Itemidx)
	{
		if (plistInventory.size() < 5)
		{
			SetInventory(listChosenUnit[Unitidx].GetItem(UnitItemidx));
			listChosenUnit[Unitidx].DeleteItem(UnitItemidx);
			return true;
		}
		return false;
	}

};


class GameManager
{
public:
	enum class E_EVENT { GAMESTART, BATTLE, CREATEALICE, DROP, GAMECLEAR, GAMEOVER, INVENTORY, MOVE, RESULT, SHOP, STANDBY };
private:
	E_EVENT m_EventNow;

	SkillManager m_SkillManager;
	EffectManager m_EffectManager;
	MapManager m_MapManager;
	ItemManager m_ItemManager;

	Player m_Player;
	Player m_Shop;


public:

	void EventGameStart()
	{

	}

	void EventCreateAlice() // �����̸� �ۼ� ������ �� �ٸ����� ġȯ�Ǹ� ����
	{

	}

	void EventStandby() // �� ������ ��ٸ��� ���ȭ�� �⺻ȭ���̶�� �� �� ����
	{

	}

	void EventMove() // ���̵� �ٸ� �̺�Ʈ ���̻��� ������Ʈ���� �߰�
	{

	}

	void EventShop() // ������ ���� ��Ÿ��
	{

	}

	void EventInventory() // �� �̵� Ȥ�� ���� �� �κ��丮�� ��������
	{

	}

	void EventDrop() // ������ ���ڸ� ���� ������ ȹ�� (Ȥ�� ����?)
	{

	}

	void EventBattle() // ���� ���� �¸� �� EventDrop���� �̵�, �й� �� ���� ����
	{
		int result = 0;
		switch (result)
		{
		case 1: EventResult();
			EventDrop();
			break;
		case 2: EventGameClear();
			break;
		case 3: EventGameOver();
			break;
		default:
			break;
		}
		
	}

	void EventResult() // ���� �� ������ ������ ��� ���
	{
		
	}

	void EventGameClear() // ���������� �¸����� ��� ���
	{

	}

	void EventGameOver() // ������ Ȥ�� �������� �й����� ��� ���
	{

	}

	void EventUpDate()
	{
		switch (m_EventNow)
		{
		case E_EVENT::CREATEALICE:
			EventCreateAlice();
			break;
		case E_EVENT::BATTLE:
			EventBattle();
			break;
		case E_EVENT::DROP:
			EventDrop();
			break;
		case E_EVENT::GAMECLEAR:
			EventGameClear();
			break;
		case E_EVENT::GAMEOVER:
			EventGameOver();
			break;
		case E_EVENT::INVENTORY:
			EventInventory();
			break;
		case E_EVENT::MOVE:
			EventMove();
			break;
		case E_EVENT::RESULT:
			EventResult();
			break;
		case E_EVENT::SHOP:
			EventShop();
			break;
		case E_EVENT::STANDBY:
			EventStandby();
			break;
		case E_EVENT::GAMESTART:
			EventGameStart();
			break;
		default:
			break;
		}
	}

	E_EVENT GetStage()
	{
		return m_EventNow;
	}

};