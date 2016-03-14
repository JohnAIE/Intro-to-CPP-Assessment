#include "Ogre.h"
#include <iostream>


Ogre::Ogre()
{
	m_name = "Ogre";
	m_maxHealth = m_health = 100;
}


Ogre::~Ogre()
{
}

void Ogre::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{		
		Creature* target = targetList[rand() % targetList.size()];

		if (target == this)
		{
			std::cout << m_name << " got confused and tried to attack himself...\n";
			return;
		}

		std::cout << m_name << " attacks " << target->GetName() << " with club...\n";

		target->ApplyDamage(this, { 40 + rand() % 20, DamageType::MELEE, Element::NONE });
	}
}

void Ogre::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	//Ogre is immune to damage less than 10 (Thick Skin)
	if (info.amount > 10)
	{		
		Creature::ApplyDamage(attacker, info);
	}
	else
	{
		std::cout << m_name << "'s thick skin blocks the puny attack.\n";
	}
}
