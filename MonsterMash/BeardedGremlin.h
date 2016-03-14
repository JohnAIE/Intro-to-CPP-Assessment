#pragma once
#include "Creature.h"
class BeardedGremlin :
	public Creature
{
public:
	BeardedGremlin();
	~BeardedGremlin();
	void Update(TargetList& targetList);
	void ApplyDamage(Creature* attacker, const DamageInfo& info);
};

