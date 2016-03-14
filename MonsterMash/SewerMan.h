#pragma once
#include "Creature.h"

class SewerMan : public Creature
{
public:
	SewerMan();
	virtual ~SewerMan();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
};