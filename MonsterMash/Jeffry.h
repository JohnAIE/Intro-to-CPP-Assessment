#pragma once
#include "Creature.h"
#include <map>
class Jeffry: public Creature
{
public:
	std::map<Element, std::string> ElementStringLookup =
	{
		{ Element::NONE, "" },
		{ Element::FIRE, "Fire" },
		{ Element::ICE, "Ice" },
		{ Element::WIND, "Wind" },
		{ Element::EARTH, "Earth" },
		{ Element::CAPTAIN_PLANET, "Captain Planet" }
	};
	Jeffry();
	virtual ~Jeffry();
	virtual void Update(TargetList& targetList);
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);
private:
	bool m_bubbleOfSafteyActive;
};

