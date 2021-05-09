#include "Skellington.h"
#include "Arena.h"

Skellington::Skellington() 
	: Creature("Resources/Images/Portraits/Portraits2_11.png")
{
	m_name = "Skellington";
	m_maxHealth = 20;
	m_health = 20;
}

Skellington::~Skellington()
{

}

void Skellington::Update(Arena& arena, TargetList& targetList)
{
	Creature* target = targetList[GetRandomValue(0, targetList.size() - 1)];

	Vector2 originalPos = GetPosition();

	if (target != this)
	{
		arena.DelayedAction(1.0f, [&arena, target, this]()
			{
				Vector2 dir = Vector2Subtract(target->GetPosition(), GetPosition());
				float len = Vector2Length(dir);
				len = len - target->GetSize().x;
				dir = Vector2Scale(Vector2Normalize(dir), len);

				Vector2 pos = Vector2Add(GetPosition(), dir);

				MoveTo(pos.x, pos.y, 0.5f, tweeny::easing::backInOut);

				return true;
			});
	}

	arena.DelayedAction(1.4f, [&arena, target, this]()
		{
			Shake(5, 0.5f);

			DamageInfo damage =
			{
				GetRandomValue(5, 10),
				DamageType::MELEE,
				Element::NONE,
			};

			target->ApplyDamage(arena, this, damage);

			return true;
		});

	arena.DelayedAction(2.5f, [&arena, target, this, originalPos]()
		{
			Vector2 pos = target->GetPosition();
			MoveTo(originalPos.x, originalPos.y, 1.0f, tweeny::easing::quadraticInOut);

			return true;
		});


	arena.DelayedAction(4.0f, [&arena, target, this]()
		{
			arena.CreatureEndTurn();
			return true;
		});	
}
