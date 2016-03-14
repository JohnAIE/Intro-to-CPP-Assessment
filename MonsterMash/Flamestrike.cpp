#include "Flamestrike.h"
#include <iostream>


Flamestrike::Flamestrike()
{
	m_name = "ParentalFigure ";
	m_maxHealth = m_health = 130;
}


Flamestrike::~Flamestrike()
{
}

void Flamestrike::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{

		Creature* target = targetList[rand() % targetList.size()];


		

		std::cout << m_name << "asks the" << target->GetName() << " to";

		int choice = rand() % 5;
		if (choice == 0)
		{
			std::cout << " Do the damn chores. " << std::endl;
		}
		else if (choice == 1)
		{
			std::cout << " Wake up for school." << std::endl;
		}
		else if (choice == 2)
		{
			std::cout << " Leave, just like you did when he was young." << std::endl;
		}
		else if (choice == 3)
		{
			std::cout << " You are a mistake and i'll never love you" << std::endl;
		}
		else if (choice == 4)
		{
			std::cout << " Get off the computer you dirty prick" << std::endl;
		}

		target->ApplyDamage(this, { 20 + rand() % 15, DamageType::MELEE, Element::NONE });
	}
}

void Flamestrike::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	//Parental figure is immune to Annoying children that deal 7 or less damage
	if (info.amount >= 7)
	{
		Creature::ApplyDamage(attacker, info);
	}
	else
	{
		std::cout << m_name << "Dont talk to back to me kid! \n";
	}
}
