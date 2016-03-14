#include "Mage.h"
#include <iostream>


Mage::Mage()
{
	m_name = "Mage";
	m_maxHealth = m_health = 200;
}


Mage::~Mage()
{
}

void Mage::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		Creature* target = targetList[rand() % targetList.size()];

		while (target == this)
		{
			target = targetList[rand() % targetList.size()];
		}

		int attack = rand() % 5;

		switch (attack)
		{
		case 0:
			std::cout << m_name << " shoots " << target->GetName() << " with a fireball...\n";
			target->ApplyDamage(this, { rand() % 40 + 10, DamageType::MAGIC, Element::FIRE });
			break;
		case 1:
			std::cout << m_name << " punches " << target->GetName() << "...\n";
			target->ApplyDamage(this, { rand() % 30 + 10, DamageType::MELEE, Element::NONE });
			break;
		case 2:
			std::cout << m_name << " pokes " << target->GetName() << " in the eye with his wand...\n";
			target->ApplyDamage(this, { rand() % 30 + 5, DamageType::MELEE, Element::NONE });
			break;
		case 3:
			std::cout << m_name << " stares menacingly at " << target->GetName() << "...it has no effect...\n";
			break;
		case 4:
			std::cout << m_name << " looks scared...\n";
			break;
		}
	}
}

void Mage::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	//Mage is strong against other magic users
	if (info.type == DamageType::MAGIC)
	{
		DamageInfo newInfo = info;
		newInfo.amount = info.amount / 2;

		Creature::ApplyDamage(attacker, newInfo);
	}
	else
	{
		Creature::ApplyDamage(attacker, info);
	}
}
