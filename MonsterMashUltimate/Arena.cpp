#include "Arena.h"

#include "raygui.h"

#include "Skellington.h"
#include <iostream>

// Arena States
// Bring in Monsters (shuffled)
// Roll for first turn
// Fight Loop
// - Move monster to center
// - Run monster logic
// - Return monster to sideline
// - Pick next monster
// Announce Winners

using namespace tweeny;

Arena::Arena()
{

	m_background = LoadTexture("Resources/Images/Background.png");

	for (int i = 0; i < 14; i++)
	{
		Creature* creature = new Skellington();
		m_creatures.push_back(creature);
	}	

	int sw = GetScreenWidth();
	int sh = GetScreenHeight();
	int r = sw * 0.76f;

	int count = m_creatures.size();
	int i = 0;

	Log("Monster Mash Ultimate is about to begin!");
	Log("");
	Log("Creatures in this Battle:");

	m_center = Vector2{ sw / 2.0f, 75 + sh / 3.0f };

	for (auto& creature : m_creatures)
	{
		float a = PI/2 + float(i) / count * PI * 2;
		creature->SetPosition(m_center.x + sw/2 * 0.7f * cosf(a), 
							  m_center.y + sh/2 * 0.5f * sinf(a));
		m_circlePosition.push_back(creature->GetPosition());
		i++;		
		Log(creature->GetName());
	}

	DelayedAction(2.0f, [=]()
		{
			if (IsLogFinished())
			{
				m_state = State::CREATURE_BEGIN_TURN;
				CreatureBeginTurn(ActiveCreature());
				return true;
			}
			return false;
		});
}

bool Arena::IsLogFinished()
{
	return m_battleLogBuffer.empty();
}

Arena::~Arena()
{
	for (auto& creature : m_creatures)
	{
		delete creature;
	}
}

void Arena::CreatureBeginTurn(Creature* creature)
{
	Log("");
	Log("%s's turn has begun", creature->GetName().c_str());

	creature->MoveTo(m_center.x, m_center.y, 1.5f, easing::quadraticInOut);
	DelayedAction(2.5f, [=]()
		{
			m_state = State::CREATURE_TURN;
			ActiveCreature()->Update(*this, m_creatures);
			return true;
		});
}

void Arena::CreatureEndTurn()
{
	Creature* creature = ActiveCreature();

	Log("");
	Log("%s's turn has ended", creature->GetName().c_str());

	Vector2 pos = m_circlePosition[m_currentTurn];
	creature->MoveTo(pos.x, pos.y, 1.5f, easing::quadraticInOut);

	DelayedAction(2.5f, [=]()
		{
			m_state = State::CREATURE_END_TURN;
			return true;
		});

	DelayedAction(3.5f, [=]()
		{
			NextCreature();
			return true;
		});
}

void Arena::NextCreature()
{
	int deadCount = 0;
	for (Creature* creature : m_creatures)
	{
		if (creature->IsDead())
		{
			deadCount++;
			if (deadCount >= m_creatures.size() - 1)
			{
				BattleEnded();
				return;
			}
		}
	}

	m_currentTurn = (m_currentTurn + 1) % int(m_creatures.size());	
	while (ActiveCreature()->IsDead())
	{
		m_currentTurn = (m_currentTurn + 1) % int(m_creatures.size());
	}

	DelayedAction(1.0f, [=]()
		{
			if (IsLogFinished())
			{
				m_state = State::CREATURE_BEGIN_TURN;
				CreatureBeginTurn(ActiveCreature());
				return true;
			}
			return false;
		});
}

void Arena::BattleEnded()
{
	m_state = State::BATTLE_ENDED;
	Log("");
	Log("The Monster Mash is Over!");

	int i = 0;
	for (Creature* creature : m_creatures)
	{
		if (!creature->IsDead())
		{
			Log("");
			Log("**** %s is the Winner ****", creature->GetName().c_str());
			Log("");
			creature->MoveTo(m_center.x, m_center.y, 1.5f, easing::quadraticInOut);
			return;
		}
		i++;
	}

	Log("");
	Log("NO ONE WON BECAUSE EVERYONE DIED >.<");
	Log("");

}

void Arena::Tick(float deltaTime)
{	
	m_delayedActions.insert(m_delayedActions.end(), m_newDelayedActions.begin(), m_newDelayedActions.end());
	m_newDelayedActions.clear();
	for (auto& tween : m_delayedActions)
	{
		tween.step(int(deltaTime * 1000));
	}
	m_delayedActions.erase(std::remove_if(m_delayedActions.begin(), m_delayedActions.end(), [](auto& tween)
	{
		return tween.direction() == -1;
	}), m_delayedActions.end());

	if (m_stateTween.duration() > 0)
	{
		m_stateTween.step(int(deltaTime * 1000));
	}

	for (auto& creature : m_creatures)
	{
		creature->Tick(deltaTime);
	}

	m_battleLogTimer += deltaTime;
	if (m_battleLogTimer > 0.01f)
	{
		m_battleLogTimer = 0.0f;
		UpdateBattleLog();
	}
}

void Arena::UpdateBattleLog()
{
	if (IsLogFinished()) return;
	char ch = m_battleLogBuffer.front();
	m_battleLogBuffer.pop();

	if (m_battleLogStrings.size() == 0)
	{
		m_battleLogStrings.push_back("");
		m_battleLogStrings.back() += ch;
	}
	else if (ch == '\n')
	{
		m_battleLogStrings.push_back("");
		LogScrollToBottom();
	}
	else
	{
		m_battleLogStrings.back() += ch;
	}
}

void Arena::LogScrollToBottom()
{
	m_battleLogScroll.y = -1000000; // TODO: calculate this properly
}

void Arena::Draw()
{
	int sw = GetScreenWidth();
	int sh = GetScreenHeight();
	const Color bgColor{ 64, 64, 64, 255 };

	DrawRectangle(0, 0, sw, sh, bgColor);

	DrawTextureEx(m_background, Vector2{ float(sw / 2 - m_background.width * 1.25f * 0.5f), -200 }, 0, 1.25f, WHITE);

	for (auto& creature : m_creatures)
	{
		creature->Draw();
	}

	if (m_state >= State::CREATURE_BEGIN_TURN && m_state <= State::CREATURE_END_TURN)
	{
		Creature* creature = ActiveCreature();
		if (creature)
		{
			auto title = creature->GetName() + "'s Turn";
			int tw = MeasureText(title.c_str(), 30);				
			DrawText(title.c_str(), GetScreenWidth() / 2 - tw / 2, 20, 30, WHITE);

			DrawCircle(creature->GetPosition().x, creature->GetPosition().y - creature->GetSize().y/2 - 30, 10 + sinf(GetTime() * 5) * 2, GREEN);
		}
	}

	// Draw Battle Log
	const int battleLogHeight = 200;
	const int battleLogInset = 20;
	const int battleLogFontSize = 20;

	const Color battleLogBgColor {244, 226, 198, 255};

	Rectangle battleLogRect{ battleLogInset,
		sh - battleLogHeight - battleLogInset,
		sw - battleLogInset * 2,
		battleLogHeight - battleLogInset };

	Rectangle battleLogContentRect
	{
		0, 0, battleLogRect.width - 14, 10 + battleLogFontSize * m_battleLogStrings.size()
	};

	char battleLogText[200] = "TEST TEXT!";

	Rectangle view = GuiScrollPanel(battleLogRect, battleLogContentRect, &m_battleLogScroll);

	BeginScissorMode(view.x, view.y, view.width, view.height);

	for (int i = 0; i < m_battleLogStrings.size(); i++)
	{
		int ty = battleLogRect.y + m_battleLogScroll.y + 10 + i * battleLogFontSize;
		if (ty + battleLogFontSize < view.y || ty > view.y + view.height) continue;

		DrawText(m_battleLogStrings[i].c_str(), 
			battleLogRect.x + m_battleLogScroll.x + 10, 
			battleLogRect.y + m_battleLogScroll.y + 10 + i * battleLogFontSize, 
			battleLogFontSize, 
			GRAY);
	}

	EndScissorMode();
	
}

void Arena::Log(const std::string& msg)
{
	for (int i = 0; i < msg.length(); i++)
		m_battleLogBuffer.push(msg[i]);
	m_battleLogBuffer.push('\n');
}
