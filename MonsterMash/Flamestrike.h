#pragma once
#include "Creature.h"

class Flamestrike :
	public Creature
{
public:

	Flamestrike();
	virtual ~Flamestrike();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
};

