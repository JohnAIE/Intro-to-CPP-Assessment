#pragma once

#include "Creature.h"

class Skellington : public Creature
{
public:
	Skellington();
	virtual ~Skellington();

	virtual void makeDecisions(Arena& arena, TargetList& targetList) override;

protected:

};

