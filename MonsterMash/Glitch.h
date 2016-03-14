#pragma once
#include "Creature.h"
class Glitch :
	public Creature
{
public:
	Glitch();
	Glitch(int curHealth);
	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
	~Glitch();
};

