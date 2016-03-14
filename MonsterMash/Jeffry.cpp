#include "Jeffry.h"
#include <iostream>



Jeffry::Jeffry()
{
	m_name = "Jeffry";
	m_maxHealth = m_health = 40;
	m_bubbleOfSafteyActive = true;
}

Jeffry::~Jeffry()
{
}

void Jeffry::Update(TargetList& targetList)
{
	if (targetList.size() > 0)
	{
		Creature* target = targetList[rand() % targetList.size()];

		if (m_health != m_maxHealth)
		{
			std::cout << m_name << " Decided to heal himself to the MAX!\n";
			m_health = m_maxHealth;
			return;
		}
		else if (!m_bubbleOfSafteyActive) {
			std::cout << m_name << " Decided to give himself a bubble of saftey. \n";
			m_bubbleOfSafteyActive = true;
			return;
		}
		while (true)
		{
			if (this == target) {
				target = targetList[rand() % targetList.size()];
			}
			else {
				break;
			}
		}
		Element elementType = (Element)(rand() % (int)Element::CAPTAIN_PLANET + 1);
		std::cout << m_name << " death stares " << target->GetName() << "\n";
		target->ApplyDamage(this, { 20 + rand() % 40, DamageType::MAGIC, elementType });
	}
}

void Jeffry::ApplyDamage(Creature* attacker, const DamageInfo& info)
{
	DamageInfo DuplacateInfo = info;
	if (info.element == Element::WIND)
	{
		DuplacateInfo.amount = 0;
		std::cout << attacker->GetName() << "'s wind attack is kinda annoying" << "\n";
		Creature::ApplyDamage(attacker, DuplacateInfo);
	}
	else if (m_bubbleOfSafteyActive)
	{
		std::cout << m_name << "'s bubble of safety protects him from the damage\n";
		m_bubbleOfSafteyActive = false;
		return;
	}
	else if (info.element == Element::NONE && info.type == DamageType::MELEE)
	{
		Creature::ApplyDamage(attacker, info);
	}
	
	else if(info.element == Element::FIRE)
	{
		DuplacateInfo.amount /= 5;
		std::cout << attacker->GetName() << "'s fire attack is super unaffective" << "\n";
		Creature::ApplyDamage(attacker, DuplacateInfo);
	}
	else if (info.element == Element::EARTH)
	{
		DuplacateInfo.amount /= 2;
		std::cout << attacker->GetName() << "'s earth attack is a little unaffective" << "\n";
		Creature::ApplyDamage(attacker, DuplacateInfo);
	}
	else if (info.element == Element::ICE)
	{
		DuplacateInfo.amount /= 4;
		std::cout << attacker->GetName() << "'s ice attack is really unaffective" << "\n";
		Creature::ApplyDamage(attacker, DuplacateInfo);
	}
	else if (info.element == Element::CAPTAIN_PLANET)
	{
		DuplacateInfo.amount /= 10;
		std::cout << attacker->GetName() << "'s Captain planet damage like does a thing(sort of)" << "\n";

		Creature::ApplyDamage(attacker, DuplacateInfo);
	}
}
