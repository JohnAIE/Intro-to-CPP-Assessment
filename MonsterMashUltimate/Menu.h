#pragma once

#include "raylib.h"
#include "tweeny.h"

#include "Arena.h"

#include <memory>

class Menu
{
public:

	enum class State
	{
		TITLE,
		ARENA
	};

	Menu();
	~Menu();

	void Tick(float deltaTime);
	void Draw();

private:

	void Start();

	State m_state {State::TITLE };
	tweeny::tween<int> m_transitionTween;
	uint8_t m_fade{ 0 };
	float m_timer { 0 };
	std::unique_ptr<Arena> m_arena;
};

