#include "Snake.h"
#include <iostream>

Snake::Snake()
{
	m_name = "Common Garden Snake";
	m_maxHealth = m_health = 5;
}


Snake::~Snake()
{
}

void Snake::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		Creature* target = targetList[rand() % targetList.size()];
		if (target != this)
		{
			std::cout << m_name << " bites " << target->getName() << " with fangs...\n";
			target->ApplyDamage(this, { 15, DamageType::MELEE, Element::NONE });
		}
	}
}

void Snake::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	if (rand() % 2 == 0 && !isDead())
	{
		std::cout << m_name << " dodges the attack!\n";
	}
	else
	{
		Creature::ApplyDamage(attacker, info);
	}
}

