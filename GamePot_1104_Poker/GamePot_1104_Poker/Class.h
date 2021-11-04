#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Effect;
class Unit;
class Skill;
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



	//100 /times \dfrac{ \text{방어력 or 마법 저항력} }{ 100 + (\text{ 방어력 or 마법 저항력 }) }100×
	//	100 + (방어력 or 마법 저항력)
};

class Unit
{
	Stat UnitStatus;
	enum E_STATUS_AILMENT { Slowdown, Silence, Faint, Aggro, Normal };
	vector<Skill> SkillList;
public:
	Unit()
	{
		SkillList.resize(4);
	}
};


class UnitManager
{
	vector<Unit*> listUnit;
};



class Effect
{

public:
	virtual void Use(Unit& caster, Unit& target) = 0;
};

// 이 뒤에 효과 추가



class EffectManager
{
	vector<Effect*> listEffect;
public:
	void Init()
	{
		// 효과 추가시 여기에 최신화
		listEffect.resize(2);
		
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
	void Ative(Unit& caster, Unit& target)
	{
		for (int i = 0; i < listEffect.size(); i++)
		{
			listEffect.at(0)->Use(caster, target);
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
		listSkill[2]->AddEffect(pEffectManager->GetEffect(1));
		listSkill[2]->AddEffect(pEffectManager->GetEffect(0));
	}
	Skill* GetSkill(int idx)
	{
		return listSkill[idx];
	}
};

class Map
{
	vector<Unit> Enemy_in_Map;
public:
	bool is_clear = false;

	void PushEnemy(Unit enemy)
	{
		Enemy_in_Map.push_back(enemy);
	}

	

};
// 이 뒤에 맵 추가


class MapManager
{
	vector<Map*> listMap;
public:
	void Init(MapManager* pMapManager)
	{
		listMap.resize(4);
	}
};


class GameManager
{
public:
	GameManager()
	{
		//m_SkillManager = new SkillManager;
	}

	void MapChanger() // 맵이동
	{

	}

	void Battle()
	{

	}

private:
	SkillManager m_SkillManager;
	EffectManager m_EffectManager;
	MapManager m_MapManager;
};