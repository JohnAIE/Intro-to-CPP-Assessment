#pragma once
#include "Creature.h"
class Snake :
	public Creature
{
public:
	Snake();
	virtual ~Snake();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);

};

