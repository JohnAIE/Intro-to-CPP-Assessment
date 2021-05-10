#include "Creature.h"
#include "Arena.h"

#include "raymath.h"
#include "rlgl.h"

#include <sstream>
#include <map>

std::map<Element, std::string> ElementStringLookup =
{
	{Element::NONE, "" },
	{Element::FIRE, "Fire"},
	{Element::ICE, "Ice" },
	{Element::WIND, "Wind" },
	{Element::EARTH, "Earth"},
	{Element::LOVE, "Love"},
	{Element::PICKLED, "Pickled"},
	{Element::SURPRISE, "Surprise"},
	{Element::RADIATION, "Radiation"},
	{Element::CAPTAIN_PLANET, "Captain Planet"}
};

std::map<DamageType, std::string> DamageTypeStringLookup =
{
	{ DamageType::MELEE, "Melee" },
	{ DamageType::RANGED, "Ranged" },
	{ DamageType::MAGIC, "Magic" }
};

Creature::Creature(const std::string& portrait)
{
	m_portrait = LoadTexture(portrait.c_str());
}

Creature::~Creature()
{
	UnloadTexture(m_portrait);
}

void Creature::draw()
{
	// Base position
	int px = m_position.x + m_shakeOffset.x - m_size.x / 2;
	int py = m_position.y + m_shakeOffset.y - m_size.y / 2;

	// Shadow
	BeginBlendMode(BlendMode::BLEND_ALPHA);
	DrawEllipse(px + m_size.x / 2, py + m_size.y + 20, int(m_size.x * 0.55), m_size.y / 8, Color{ 0, 0, 0, 64 });
	EndBlendMode();

	float saturation = isDead() ? 0.0f : 1.0f;

	// Portrait
	//rlPushMatrix();
	Rectangle rect { px + m_walkOffset.x, py + m_walkOffset.y, m_size.x, m_size.y };
	Rectangle src { 0, 0, m_portrait.width, m_portrait.height };	
	DrawRectangleGradientV(rect.x + m_walkOffset.x, rect.y + m_walkOffset.y, m_size.x, m_size.y, m_bgColor, BLACK);	
	DrawTexturePro(m_portrait, src, rect, Vector2{ 0, 0 }, 0, isDead() ? DARKGRAY : WHITE);
	//rlPopMatrix();

	BeginBlendMode(BlendMode::BLEND_ADDITIVE);
	DrawRectanglePro(rect, Vector2{ 0,0 }, 0, m_tint);
	EndBlendMode();

	Vector3 outline = ColorToHSV(m_outlineColor);
	outline.y *= saturation;
	DrawRectangleLinesEx(rect, 3, ColorFromHSV(outline));

	// Name
	const int nameFontSize = 18;
	auto& name = getName();
	int textWidth = MeasureText(name.c_str(), nameFontSize);
	DrawText(name.c_str(), px + m_size.x / 2 - textWidth / 2, py - nameFontSize - 2, nameFontSize, LIGHTGRAY);

	// Health Bar
	const int healthbarHeight = 20;
	const int healthbarInset = 4;
	float healthPercent = Clamp(float(m_health) / m_maxHealth, 0.0f, 1.0f);

	DrawRectangleGradientH(px, py + m_size.y, m_size.x, healthbarHeight, ColorFromHSV({ 0, 0.8f * saturation, 0.5f }), ColorFromHSV({ 0, 0.8f * saturation, 0.4f }));
	DrawRectangleGradientH(px + healthbarInset, 
						   py + m_size.y + healthbarInset, 
						   (m_size.x - healthbarInset * 2) * healthPercent, 
						   healthbarHeight - healthbarInset * 2, 
						   ColorFromHSV({ healthPercent * 90 + 30, 0.9f * saturation, 0.4f }), ColorFromHSV({ healthPercent * 120 + 30, 0.9f * saturation, 0.9f }));
}

void Creature::applyDamage(Arena& arena, Creature* attacker, const DamageInfo& info)
{
	std::string damageName = DamageTypeStringLookup[info.type];
	std::string elementName = ElementStringLookup[info.element];

	std::stringstream txt;

	if (isDead())
	{
		txt << m_name << "'s corpse ";
	}
	else
	{
		txt << m_name;
	}

	txt << " took "
		<< info.amount << " "
		<< damageName;

	if (info.element != Element::NONE)
	{
		txt << " " << elementName;
	}

	txt
		<< " damage from "
		<< attacker->getName();

	if (m_health > 0 && m_health - info.amount <= 0)
	{
		txt << "\n";
		if (m_health - info.amount < -m_maxHealth)
		{
			txt << m_name << " explodes into a fine pink mist!";
		}
		else
		{
			txt << m_name << " dies!";
		}
	}

	m_health -= info.amount;

	shake(10, 0.5f);
	flash(Color{ 128, 128, 128 }, 0.5f);

	if (attacker == this)
	{
		txt << "\n" << m_name << " hurt itself in it's confusion...";
	}

	arena.log(txt.str());
}

void Creature::tick(float deltaTime)
{
	if (m_moveTween.duration() > 0)
	{
		auto xy = m_moveTween.step(uint32_t(deltaTime * 1000));
		m_position.x = xy[0];
		m_position.y = xy[1];

		float speed = Vector2Length(Vector2Subtract(m_position, m_prevPosition));
		if (speed > 0.1f)
		{			
			m_walkCycle += speed;
			m_walkOffset = Vector2{ 0, fabsf(sinf(m_walkCycle * 0.05f)) * -5.0f };
		}
		else
		{
			m_walkOffset = Vector2Scale(m_walkOffset, 0.9f);
		}

		m_prevPosition = m_position;
	}
	else
	{
		m_walkOffset = Vector2Zero();
	}

	if (m_tintTween.duration() > 0)
	{
		auto rgb = m_tintTween.step(uint32_t(deltaTime * 1000));
		m_tint.r = rgb[0];
		m_tint.g = rgb[1];
		m_tint.b = rgb[2];
	}

	if (m_shakeTween.duration() > 0)
	{
		m_shakeAmount = m_shakeTween.step(uint32_t(deltaTime * 1000));
		if (m_shakeAmount > 0)
		{
			m_shakeOffset.x = GetRandomValue(-m_shakeAmount, m_shakeAmount);
			m_shakeOffset.y = GetRandomValue(-m_shakeAmount, m_shakeAmount);
		}
		else
		{
			m_shakeOffset = Vector2Zero();
		}
	}
}