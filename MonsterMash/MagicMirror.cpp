#include "MagicMirror.h"
#include <iostream>


MagicMirror::MagicMirror()
{
	m_name = "Magic Mirror";
	m_maxHealth = m_health = 120;
	m_bonusDamage = 1;
}


MagicMirror::~MagicMirror()
{
}

void MagicMirror::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		Creature* target = targetList[rand() % targetList.size()];
		if (target != this && target)
		{
			std::cout << m_name << " attacks " << target->GetName() << " with light beam...\n";

			target->ApplyDamage(this, { 10 + rand() % m_bonusDamage, DamageType::RANGED, Element::FIRE });	
		}
	}
}

void MagicMirror::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	m_bonusDamage += info.amount;
	Creature::ApplyDamage(attacker, info);
}

