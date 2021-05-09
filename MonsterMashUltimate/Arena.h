#pragma once

#include "Creature.h"

#include "tweeny.h"
#include "raymath.h"
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

class Arena
{
public:

	enum class State
	{
		BATTLE_BEGIN,
		CREATURE_BEGIN_TURN,
		CREATURE_TURN,
		CREATURE_END_TURN,
		BATTLE_ENDED,
	};

	Arena();
	~Arena();

	void Tick(float deltaTime);
	void UpdateBattleLog();
	void Draw();

	void Log(const std::string& msg);

	template <typename ... Args>
	void Log(const char* msg, Args&&... args)
	{
		static char buff[1024];		
		sprintf_s(buff, 1024, msg, std::forward<Args>(args)...);
		for (int i = 0; i < strlen(buff); i++)
			m_battleLogBuffer.push(buff[i]);
		m_battleLogBuffer.push('\n');
		//m_battleLogStream << buff << std::endl;
	}

	bool IsLogFinished();
	void LogScrollToBottom();

	void CreatureBeginTurn(Creature* creature);
	void CreatureEndTurn();
	void NextCreature();
	void BattleEnded();

	Creature* ActiveCreature()
	{
		auto iter = m_creatures.begin();
		std::advance(iter, m_currentTurn);
		return *iter;
	}

	template <typename CallbackT>
	void DelayedAction(float delay, CallbackT t)
	{
		m_newDelayedActions.emplace_back(tweeny::from(0).to(1).during(delay * 1000).onStep([t](auto& tween, int)
			{
				if (tween.progress() >= 1.0f && t())
				{
					tween.backward();
				}
				return false;
			}));
	}

private:

	std::list<tweeny::tween<int>> m_newDelayedActions;
	std::list<tweeny::tween<int>> m_delayedActions;

	State m_state { State::BATTLE_BEGIN };
	tweeny::tween<State> m_stateTween;
	int m_currentTurn{ 0 };
	Vector2 m_center;

	std::vector<Creature*> m_creatures;
	std::vector<Vector2> m_circlePosition;;
	Vector2 m_battleLogScroll{ 0,0 };

	std::queue<char> m_battleLogBuffer;
	//std::stringstream m_battleLogStream;
	std::vector<std::string> m_battleLogStrings;
	float m_battleLogTimer { 0 };

	Texture2D m_background;
};

