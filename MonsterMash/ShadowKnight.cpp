#include "ShadowKnight.h"
#include <iostream>
using namespace std;


ShadowKnight::ShadowKnight()
{
	m_name = "Shadow Knight";
	m_health = 90;
	m_maxHealth = 90;
	defending = false;
}


ShadowKnight::~ShadowKnight()
{
}

void ShadowKnight::Update(TargetList & targetList)
{
	stratergy = GetStrategy(targetList);
	defending = false;
	switch (stratergy)
	{
	case defend:
		Defend(targetList);
		break;

	case attack:
		Attack(targetList);
		break;

	case heal:
		Heal(targetList);
		break;
	}
}

void ShadowKnight::ApplyDamage(Creature * attacker, const DamageInfo & info)
{
	int damage = info.amount;
	if (defending)
	{
		cout << m_name << " takes reduced damage as it is defending\n";
		damage /= 5;
	}
	if (info.element == Element::CAPTAIN_PLANET)
	{
		cout << m_name << " is immune to Captain Planet\n";
		damage = 0;
	}
	Creature::ApplyDamage(attacker, { damage, info.type, info.element });
}

void ShadowKnight::Attack(TargetList & targetList)
{
	Creature* target;
	int count = 0;
	do
	{
		target = targetList[rand() % targetList.size()];
		if (count > 100)
		{
			cout << m_name << " couldn't find a target!\n";
			return;
		}
		count++;
	} 
	while (target->isDead());

	int dice = rand() % 100;
	if (dice < 1)
	{
		cout << m_name << " uses infernal powers to steal " << target->getName() << "'s soul\n";
		m_health += target->getHealth();
		target->ApplyDamage(this, { 10000, DamageType::MAGIC, Element::NONE });
	}
	else if (dice < 25)
	{
		cout << m_name << " casts a ball of fire at " << target->getName() << "\n";
		target->ApplyDamage(this, { 40, DamageType::MAGIC, Element::FIRE });
	}
	else if (dice < 50)
	{
		cout << m_name << " chills " << target->getName() << "with an icy grip\n";
		target->ApplyDamage(this, { 30, DamageType::MELEE, Element::ICE });
	}
	else
	{
		cout << m_name << " attacks " << target->getName() << endl;
		target->ApplyDamage(this, { 25, DamageType::MELEE, Element::NONE });
	}
}

void ShadowKnight::Defend(TargetList & targetList)
{
	cout << m_name << " defends itself\n";
	defending = true;
}

void ShadowKnight::Heal(TargetList & targetList)
{
	cout << m_name << " heals itself\n";
	m_health += 30;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}

int ShadowKnight::GetStrategy(TargetList & targetList)
{
	int livingFighters = 0;
	for (auto f : targetList)
	{
		if (!f->isDead())
		{
			livingFighters++;
		}
	}
	if (((float)m_health / (float)m_maxHealth) < 0.5)
	{
		return heal;
	}
	else if (livingFighters > 5)
	{
		return defend;
	}
	else if (livingFighters > 2)
	{
		if (rand() % 100 < 90)
		{
			return defend;
		}
		else
		{
			return attack;
		}
	}
	else
	{
		return attack;
	}
}
