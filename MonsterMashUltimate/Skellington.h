#pragma once

#include "Creature.h"

class Skellington : public Creature
{
public:
	Skellington();
	virtual ~Skellington();

	virtual void Update(Arena& arena, TargetList& targetList);

protected:

};

