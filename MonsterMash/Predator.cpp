#include "Predator.h"
#include <iostream>


Predator::Predator()
{
	m_name = "Predator";
	m_maxHealth = m_health = 100;
	m_invisible = false;
	int m_invisibleCountdown = 0;
}


Predator::~Predator()
{

}


void Predator::Update(TargetList & targetList)
{
	if (targetList.size() > 0)
	{
		if (m_invisible)
		{
			if (m_invisibleCountdown > 0)
			{
				m_invisibleCountdown -= 1;
			}

			if (m_invisibleCountdown <= 0)
			{
				m_invisible = false;
			}
		}

		Creature* target = targetList[rand() % targetList.size()];

		if (target == this && m_health > 80)
		{
			if (m_invisibleCountdown = 0)
			{
				m_invisible = true;
				m_invisibleCountdown = 3;
			}
		}

		else if (target == this && m_invisible == false)
		{
			std::cout << m_name << " Decided to self heal himself... \n";
			m_health += 30;
			return;
		}

		std::cout << m_name << " attacks " << target->getName() << " with wrist blades ... \n";

		if (m_invisible == false)
		{
			target->ApplyDamage(this, { 35 + rand() % 15, DamageType::MELEE, Element::NONE });
		}
	}
}


void Predator::ApplyDamage(Creature * attacker, const DamageInfo & info)
{
	if (m_invisible == false)
	{
		Creature::ApplyDamage(attacker, info);
	}

	else if (m_invisible == true)
	{

	}	
}
