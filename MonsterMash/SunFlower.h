#pragma once
#include "Creature.h"

class SunFlower :
	public Creature
{
public:

	SunFlower();
	virtual ~SunFlower();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
};

