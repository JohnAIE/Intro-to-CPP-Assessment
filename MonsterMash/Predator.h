#pragma once
#include "Creature.h"

class Predator :
	public Creature
{
public:

	Predator();
	virtual~Predator();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);

protected:
	bool m_invisible;
	int m_invisibleCountdown;
};

