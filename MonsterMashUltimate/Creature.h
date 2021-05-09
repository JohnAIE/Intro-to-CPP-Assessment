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
	typedef tweeny::tween<unsigned char, unsigned char, unsigned char> TintTween;

	Creature(const std::string& portrait);
	virtual ~Creature();

	void Tick(float deltaTime);
	virtual void Update(Arena& arena, TargetList& targetList) = 0;
	virtual void Draw();
	virtual void ApplyDamage(Arena& arena, Creature* attacker, const DamageInfo& info);

	const std::string& GetName()
	{
		return m_name;
	}

	int GetHealth()
	{
		return m_health;
	}

	bool IsDead()
	{
		return m_health <= 0;
	}

	Creature* AddPrefix(const std::string& prefix)
	{
		m_name = prefix + " " + m_name;
		return this;
	}

	Vector2 GetPosition()
	{
		return m_position;
	}

	Vector2 GetSize()
	{
		return m_size;
	}

	void SetPosition(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
		m_prevPosition = m_position;
	}

	template<typename EasingT>
	PositionTween& MoveTo(int x, int y, float time, EasingT easing = tweeny::easing::linear)
	{
		//tweeny::from(0).to(1).during(int(time * 1000)).via(easing).onStep([=](auto& tween, float t)
		//	{
		//		
		//	});
		m_moveTween = tweeny::from(int(m_position.x), int(m_position.y)).to(x, y).during(int(time * 1000)).via(easing);
		return m_moveTween;
	}

	tweeny::tween<int>& Shake(int amount, float duration)
	{
		m_shakeTween = tweeny::from(amount).to(0).during(int(duration * 1000));
		return m_shakeTween;
	}

	TintTween& Flash(Color color, float duration)
	{
		m_tintTween = tweeny::from(m_tint.r, m_tint.g, m_tint.b)
			.to(color.r, color.g, color.b)
			.during(int(duration * 500))
			.to(m_tint.r, m_tint.g, m_tint.b).during(int(duration * 500))
			.via(tweeny::easing::quadraticInOut);
		return m_tintTween;
	}
	
	// MoveTo().Wait().Action().RotateTo().RotateBy()...

	// PunchAndReturn()
	// Shake()
	// Flash()
	// Squash()
	// Flip()


protected:
	// Data
	int m_health { 100 };
	int m_maxHealth { 100 };
	std::string m_name;

	// Appearance
	Texture2D m_portrait;
	Color m_tint = BLACK;
	Color m_bgColor = GRAY;
	Color m_outlineColor = YELLOW;	

	Vector2 m_position { 100, 100 };
	Vector2 m_prevPosition;
	Vector2 m_shakeOffset { 0, 0 };
	int m_shakeAmount{ 0 };
	float m_elevation { 0 };
	float m_rotation { 0 };
	Vector2 m_size { 75, 75 };
	Vector2 m_walkOffset{ 0, 0 };
	float m_walkCycle { 0 };

	// Animation
	std::queue<tweeny::tween<float>> m_tweens;

	PositionTween m_moveTween;
	tweeny::tween<int> m_shakeTween;
	TintTween m_tintTween;
};

