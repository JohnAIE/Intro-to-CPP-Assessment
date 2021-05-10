#include "Menu.h"
#include "raygui.h"
#include "raymath.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Tick(float deltaTime)
{
	m_timer += deltaTime;

	if (m_transitionTween.duration() > 0)
	{
		m_fade = m_transitionTween.step(uint32_t(deltaTime* 1000));
	}

	switch (m_state)
	{
	case State::ARENA:
		m_arena->update(deltaTime);
		break;
	default:
		break;
	}
}

void Menu::Draw()
{
	int sw = GetScreenWidth();
	int sh = GetScreenHeight();


	switch (m_state)
	{
	case State::TITLE:
	{
		const char* title = "Welcome to Monster Mash Ultimate!";
		int tw = MeasureText(title, 30);
		DrawText(title, sw / 2 - tw / 2 + 5, 100 + 5, 30, Color{32, 32, 32, 255});
		DrawText(title, sw/2 - tw/2, 100 + int(sinf(m_timer * 2.0f) * 5), 30, LIGHTGRAY);
			
		if (GuiButton(Rectangle{ sw / 2.0f - 100.0f, 200.0f, 200.0f, 75.0f }, "START"))
		{
			Start();
		}

		break;
	}
	case State::ARENA:
	{
		m_arena->draw();
		break;
	}
	default:
		break;
	}

	if (m_fade > 0)
	{
		BeginBlendMode(BLEND_ALPHA);
		DrawRectangle(0, 0, sw, sh, Color{ 0,0,0,m_fade });
		EndBlendMode();
	}
}

void Menu::Start()
{
	if (m_state == State::TITLE && m_transitionTween.duration() == 0)
	{
		m_transitionTween = tweeny::from<int>(0).to(255).during(100).to(0).during(100).onStep([=](auto& tween, int a)
			{
				if (tween.progress() >= 0.5f && m_state == State::TITLE)
				{
					m_state = State::ARENA;
					m_arena = std::make_unique<Arena>();
				}

				if (tween.progress() >= 1.0f)
				{
					return true;
				}
				return false;
			});
	}
}