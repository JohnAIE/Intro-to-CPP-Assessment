#pragma once
#include "Creature.h"

class MagicMirror :
	public Creature
{
public:
	MagicMirror();
	virtual ~MagicMirror();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);

protected:
	int m_bonusDamage;
};

