#include "SunFlower.h"
#include <iostream>

SunFlower::SunFlower()
{
	m_name = "Killer Flower";
	m_maxHealth = m_health = 75;
}

void SunFlower::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		if (m_health >= 40)
		{
			Creature* target = targetList[rand() % targetList.size()];
			if (target != this)
			{
				std::cout << m_name << " danced around " << target->GetName() << "...\n";
				target->ApplyDamage(this, { 10, DamageType::MELEE, Element::EARTH });
			}
		}
		else
		{
			m_health += 10;
			std::cout << m_name << " has just healed 10 health. It now has "<< m_health << " health left.\n" ;
		}
		
	}
}

void SunFlower::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	if (info.amount > 50)
	{
		std::cout << m_name << " is so bright that it put the attacker off, and made it do less damage.\n";
		DamageInfo info2(info);
		info2.amount /= 2;
		Creature::ApplyDamage(attacker, info2);
	}
	else
	{
		Creature::ApplyDamage(attacker, info);
	}
}

SunFlower::~SunFlower()
{
}
