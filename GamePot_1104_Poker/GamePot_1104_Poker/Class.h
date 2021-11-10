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
	// 52까지해서 스페이드, 다이아, 하트 ,클로버를 표현 추가유닛은 그 뒤에 배정
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
		// 스탯은 9개 스다하클 0번째 유닛은 
		m_listFriendlyUnit[0] = Unit("앨리스", 0, Stat(100, 100, 100, 100, 100, 100, 100, 100, 100));
		m_listFriendlyUnit[1] = Unit("스페이드에이스", 1, Stat(10, 5, 3, 0, 0, 0, 10, 0, 20));
		//이렇게 52개

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

// 이 뒤에 효과 추가

class Heal : public Effect
{
	
public:
	void Use(Unit& caster, Unit& target)
	{
		target.UnitStatus.n_HP += caster.UnitStatus.n_AP * m_percent / 100;
	}

	string GetType()
	{
		string type = "치유";
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
		string type = "물리공격";
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
		string type = "마법공격";
		return type;
	}
};


class EffectManager
{
	vector<Effect*> listEffect;
public:
	void Init()
	{
		// 효과 추가시 여기에 최신화
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
		// 이 뒤에 스킬 추가(효과를 조합) 및 갯수 최신화
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

// 이 뒤에 맵 추가


class MapManager
{
	vector<Map*> listMap;
	// 스테이지를 만들기
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
	//////////////////// 인벤토리 관련 함수 /////////////////////////

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

	/////////////////// 상점 관련 함수 /////////////////////////

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

	/////////////////// 유닛 관련 함수 /////////////////////////

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

	void EventCreateAlice() // 유저이름 작성 하지만 다 앨리스로 치환되며 시작
	{

	}

	void EventStandby() // 맵 선택을 기다리는 대기화면 기본화면이라고도 할 수 있음
	{

	}

	void EventMove() // 맵이동 다른 이벤트 사이사이 업데이트마다 추가
	{

	}

	void EventShop() // 아이템 샵이 나타남
	{

	}

	void EventInventory() // 맵 이동 혹은 전투 중 인벤토리를 볼수있음
	{

	}

	void EventDrop() // 아이템 상자를 열어 아이템 획득 (혹은 함정?)
	{

	}

	void EventBattle() // 적을 만남 승리 시 EventDrop으로 이동, 패배 시 게임 오버
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

	void EventResult() // 생존 시 전투가 끝나고 결과 출력
	{
		
	}

	void EventGameClear() // 보스전에서 승리했을 경우 출력
	{

	}

	void EventGameOver() // 보스전 혹은 전투에서 패배했을 경우 출력
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