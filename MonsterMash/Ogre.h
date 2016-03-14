#pragma once
#include "Creature.h"

class Ogre :
	public Creature
{
public:

	Ogre();
	virtual ~Ogre();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
};

