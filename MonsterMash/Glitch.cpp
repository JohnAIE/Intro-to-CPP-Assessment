#include "Glitch.h"
#include "Creature.h"
#include <iostream>
#include <map>

std::map<Element, std::string> EStringLookup =
{
	{ Element::NONE, "" },
	{ Element::FIRE, "Fire" },
	{ Element::ICE, "Ice" },
	{ Element::WIND, "Wind" },
	{ Element::EARTH, "Earth" },
	{ Element::CAPTAIN_PLANET, "Captain Planet" }
};

std::map<DamageType, std::string> DTypeStringLookup =
{
	{ DamageType::MELEE, "Melee" },
	{ DamageType::RANGED, "Ranged" },
	{ DamageType::MAGIC, "Magic" }
};

Glitch::Glitch()
{
	m_name = new char[15];
	m_name[14] = 0;
	m_maxHealth = 1 + (rand() % 250);
	m_health = m_maxHealth;
}

Glitch::Glitch(int curHealth)
{
	m_name = new char[15];
	m_name[14] = 0;
	m_maxHealth = 1 + (rand() % 200);
	m_health = __min(m_maxHealth, curHealth);
}

void Glitch::Update(TargetList & targetList)
{
	int numTargs = rand() % targetList.size();
	for (int i = 0; i < numTargs; i++)
	{
		DamageInfo d;
		d.amount = rand() % 100;
		d.element = Element::CAPTAIN_PLANET;
		d.type = DamageType::MAGIC;
		targetList[rand() % targetList.size()]->ApplyDamage(this, d);
	}
	if (rand() % 100 < 15)
	{
		int targ = rand() % targetList.size();
		std::cout << targetList[targ]->getName() << " implodes, turning into a jumble of distorted characters!/n";
		int h = targetList[targ]->getHealth();
		targetList[targ] = new Glitch();
	}
}

void Glitch::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	std::string damageName = DTypeStringLookup[info.type];
	std::string elementName = EStringLookup[info.element];

	if (isDead())
	{
		std::cout << m_name << "'s corpse ";
	}
	else
	{
		std::cout << m_name;
	}

	std::cout << "took "
		<< info.amount << " "
		<< damageName;

	if (info.element != Element::NONE)
	{
		std::cout << " " << elementName;
	}

	std::cout
		<< " damage from "
		<< attacker->getName() << "\n";

	if (m_health > 0 && m_health - info.amount <= 0)
	{
		if (m_health - info.amount < -m_maxHealth)
		{
			std::cout << m_name << " collapses into raw bits!\n";
			std::cout << attacker->getName() << " starts imploding, turning into a jumble of distorted characters!/n";
			int h = attacker->getHealth();
			attacker = new Glitch();
		}
		else
		{
			std::cout << m_name << " dies!\n";
		}
	}

	m_health -= info.amount;
}

Glitch::~Glitch()
{
}
