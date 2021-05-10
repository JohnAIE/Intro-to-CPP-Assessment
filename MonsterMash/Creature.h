#pragma once

#include <vector>
#include <string>

enum class DamageType
{
	MELEE,
	RANGED, 
	MAGIC
};

enum class Element
{
	NONE,
	FIRE,
	ICE,
	WIND,
	EARTH,
	CAPTAIN_PLANET
};

struct DamageInfo
{
	int amount;
	DamageType type;
	Element element;
};

class Creature
{
public:

	typedef std::vector<Creature*> TargetList;

	Creature();
	virtual ~Creature();

	virtual void Update(TargetList& targetList) = 0;
	virtual void ApplyDamage(Creature* attacker, const DamageInfo& info);

	const std::string& getName()
	{
		return m_name;
	}

	int getHealth()
	{
		return m_health;
	}

	bool isDead()
	{
		return m_health <= 0;
	}

	Creature* addPrefix(const std::string& prefix)
	{
		m_name = prefix + " " + m_name;
		return this;
	}

protected:
	int m_health;
	int m_maxHealth;
	std::string m_name;
};

