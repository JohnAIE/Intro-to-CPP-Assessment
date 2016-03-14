#include "Creature.h"

#include <iostream>
#include <map>

std::map<Element, std::string> ElementStringLookup = 
{
	{Element::NONE, "" },
	{Element::FIRE, "Fire"},
	{Element::ICE, "Ice" },
	{Element::WIND, "Wind" },
	{Element::EARTH, "Earth"},
	{Element::CAPTAIN_PLANET, "Captain Planet"}
};

std::map<DamageType, std::string> DamageTypeStringLookup =
{
	{ DamageType::MELEE, "Melee" },
	{ DamageType::RANGED, "Ranged" },
	{ DamageType::MAGIC, "Magic" }
};

Creature::Creature()
{
}

Creature::~Creature()
{
}

void Creature::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	std::string damageName = DamageTypeStringLookup[info.type];
	std::string elementName = ElementStringLookup[info.element];

	if (IsDead())
	{
		std::cout << m_name << "'s corpse ";
	}
	else
	{
		std::cout << m_name;
	}

	std::cout << " took "
		<< info.amount << " "
		<< damageName;

	if (info.element != Element::NONE)
	{
		std::cout << " " << elementName;
	}

	std::cout 
			  << " damage from " 
			  << attacker->GetName() << "\n";			

	if (m_health > 0 && m_health - info.amount <= 0)
	{
		if (m_health - info.amount < -m_maxHealth)
		{
			std::cout << m_name << " explodes into a fine pink mist!\n";
		}
		else
		{
			std::cout << m_name << " dies!\n";
		}
	}

	m_health -= info.amount;
}
