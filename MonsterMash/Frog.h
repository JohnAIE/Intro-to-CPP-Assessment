#pragma once
#include "Creature.h"

class Frog :
	public Creature
{
public:

	Frog();
	virtual ~Frog();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
};

#pragma once
