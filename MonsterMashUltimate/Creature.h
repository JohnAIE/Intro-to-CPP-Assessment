#pragma once

#include "raylib.h"
#include "tweeny.h"

#include <list>
#include <queue>
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
	LOVE,
	PICKLED,
	SURPRISE,
	RADIATION,
	CAPTAIN_PLANET
};

struct DamageInfo
{
	int amount;
	DamageType type;
	Element element;
};

class Arena;

class Creature
{
public:

	typedef std::vector<Creature*> TargetList;
	typedef tweeny::tween<int, int> PositionTween;
	typedef tweeny::tween<int> ShakeTween;
	typedef tweeny::tween<unsigned char, unsigned char, unsigned char> TintTween;

	Creature(const std::string& portrait);
	virtual ~Creature();

	// Called once per frame to update the creature's state
	void tick(float deltaTime);
	virtual void makeDecisions(Arena& arena, TargetList& targetList) = 0;
	virtual void draw();
	virtual void applyDamage(Arena& arena, Creature* attacker, const DamageInfo& info);
	virtual void onUpdate(float deltaTime) {};
	virtual void onPreDraw() {};
	virtual void onPostDraw() {};


	const std::string& getName()
	{
		return m_name;
	}

	int getHealth()
	{
		return m_health;
	}

	int getMaxHealth()
	{
		return m_maxHealth;
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

	Vector2 getSize()
	{
		return m_size;
	}

	Vector2 getPosition()
	{
		return m_position;
	}

	void setPosition(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
		m_prevPosition = m_position;
	}

	template<typename EasingT>
	PositionTween& moveTo(int x, int y, float time, EasingT easing = tweeny::easing::linear)
	{
		m_moveTween = tweeny::from(int(m_position.x), int(m_position.y)).to(x, y).during(int(time * 1000)).via(easing);
		return m_moveTween;
	}

	ShakeTween& shake(int amount, float duration)
	{
		m_shakeTween = tweeny::from(amount).to(0).during(int(duration * 1000));
		return m_shakeTween;
	}

	TintTween& flash(Color color, float duration)
	{
		m_tintTween = tweeny::from(m_tint.r, m_tint.g, m_tint.b)
			.to(color.r, color.g, color.b)
			.during(int(duration * 500))
			.to(m_tint.r, m_tint.g, m_tint.b).during(int(duration * 500))
			.via(tweeny::easing::quadraticInOut);
		return m_tintTween;
	}
	
protected:
	// State / Data
	std::string m_name;
	int m_health { 100 };
	int m_maxHealth { 100 };	

	// Appearance
	Texture2D m_portrait;
	Color m_tint = BLACK;
	Color m_bgColor = GRAY;
	Color m_outlineColor = YELLOW;	

	// Visual state
	Vector2 m_position { 100, 100 };
	Vector2 m_prevPosition;
	Vector2 m_shakeOffset { 0, 0 };
	int m_shakeAmount{ 0 };
	float m_elevation { 0 };
	float m_rotation { 0 };
	Vector2 m_size { 75, 75 };
	Vector2 m_walkOffset{ 0, 0 };
	float m_walkCycle { 0 };

	// Animation tweens
	PositionTween m_moveTween;
	ShakeTween m_shakeTween;
	TintTween m_tintTween;
};

