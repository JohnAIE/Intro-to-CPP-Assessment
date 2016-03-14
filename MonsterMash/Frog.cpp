#include "Frog.h"
#include <iostream>


Frog::Frog()
{
	m_name = "Frog";
	m_maxHealth = m_health = 100;
}

Frog::~Frog()
{

}



void Frog::Update(TargetList& targetlist)
{
	if (targetlist.size() > 0)
	{
		Creature* target = targetlist[rand() % targetlist.size()];

		if (target == this)
		{
			std::cout << m_name << " got confused and tried to attack himself...\n";
			return;
		}
		
		int choice = rand() % 3;
		if (choice == 0)
		{
			std::cout << m_name << " tounge punches " << target->GetName() << " in its fart box\n";

			target->ApplyDamage(this, { 30 + rand() % 20, DamageType::MELEE, Element::NONE });
		}
		if (choice == 1)
		{
			std::cout << m_name << " gives " << target->GetName() << " a tender loving lick on the side of its cheek \n";

			target->ApplyDamage(this, { 50 + rand() % 10, DamageType::MELEE, Element::NONE });
		}
		if (choice == 2)
		{
			std::cout << m_name << " gives " << target->GetName() << " the lick of health!\n";

			target->ApplyDamage(this, { -20 + rand() % -10, DamageType::MELEE, Element::NONE });
		}
		
	}
}
void Frog::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	//Ogre is immune to damage less than 10 (Thick Skin)
	if (info.amount > 0)
	{		
		Creature::ApplyDamage(attacker, info);
		
	}
}
