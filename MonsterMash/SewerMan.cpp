#include "SewerMan.h"
#include <Iostream>

SewerMan::SewerMan()
{
	m_name = "The Hero We Deserve, SEWER MAN ";
	m_maxHealth = m_health = 75;
}

SewerMan::~SewerMan()
{
}

void SewerMan::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		Creature* target = targetList[rand() % targetList.size()];
		if (target != this)
		{
			std::cout << m_name << " Sewage Blasts " << target->GetName() << " with N.Y.C Sewage Cannon!\n";
			target->ApplyDamage(this, { 25 + rand() % 15, DamageType::RANGED, Element::NONE });
		}
	}
}

void SewerMan::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	if (rand() % 5 == 0  && !IsDead())
	{
		std::cout << m_name << " uses sludge wall, nullifying the Damage!\n";
	}
	else
	{
		Creature::ApplyDamage(attacker, info);
	}
}
