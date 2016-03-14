#include "BeardedGremlin.h"
#include <iostream>


BeardedGremlin::BeardedGremlin()
{
	m_name = "Bearded Gremlin";
	m_maxHealth = m_health = 50;
}

BeardedGremlin::~BeardedGremlin()
{
}

void BeardedGremlin::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		int mostHealth = 0;
		for (int i = 0; i < targetList.size(); i++)
		{			
			Creature* target = targetList[i];
			if (target->GetHealth() > mostHealth)
			{
				mostHealth = target->GetHealth();
			}			
		}
		for (int i = 0; i < targetList.size(); i++)
		{
			Creature* target = targetList[i];
			if (target->GetHealth() == mostHealth)
			{
				std::cout << m_name << " punches " << target->GetName() << " with its fists...\n";
				target->ApplyDamage(this, { 50, DamageType::MELEE, Element::NONE });
			}
		}
		
		
	}
}

void BeardedGremlin::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	if (rand() % 3 == 0 && !IsDead())
	{
		std::cout << m_name << " dodges the attack!\n";
	}
	else
	{
		Creature::ApplyDamage(attacker, info);
	}
}