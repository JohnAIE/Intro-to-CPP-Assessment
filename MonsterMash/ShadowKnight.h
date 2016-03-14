#pragma once
#include "Creature.h"
class ShadowKnight :
	public Creature
{
public:
	enum {defend, attack, heal};
	ShadowKnight();
	~ShadowKnight();

	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);

private:
	int stratergy;
	bool defending;

	void Attack(TargetList& targetList);
	void Defend(TargetList& targetList);
	void Heal(TargetList& targetList);
	int GetStrategy(TargetList& targetList);
};

