/*
	Mage created by Jack Vine.

	Strengths:	Strong against magic attacks.
				Wont attack itself.
				Fair amount of health.

	Weaknesses:	Many weak attacks.
				Some attacks are useless.
*/

#pragma once
#include "Creature.h"

class Mage : public Creature
{
public:
	Mage();
	virtual ~Mage();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
};

