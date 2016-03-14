#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>

#include "Creature.h"
#include "Ogre.h"
#include "Snake.h"

// Custom Creatures
#include "Mage.h"
#include "SunFlower.h"
#include "BeardedGremlin.h"
#include "Predator.h"
#include "Frog.h"
#include "SewerMan.h"
#include "Jeffry.h"
#include "Glitch.h"
#include "Flamestrike.h"
#include "MagicMirror.h"
#include "ShadowKnight.h"

void sleep(float time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(time * 1000)));
}

int main()
{
	srand(time(NULL));
	std::vector<Creature*> creatureList;

	creatureList.push_back(new Jeffry());
	creatureList.push_back(new SunFlower());
	//creatureList.push_back(new Predator());
	creatureList.push_back(new Frog());
	creatureList.push_back(new Mage());
	creatureList.push_back(new SewerMan());
	creatureList.push_back(new Flamestrike());
	creatureList.push_back(new Glitch());
	creatureList.push_back(new BeardedGremlin());	
	creatureList.push_back(new MagicMirror());
	creatureList.push_back(new ShadowKnight());
	creatureList.push_back(new Snake());


	//creatureList.push_back((new Ogre())->AddPrefix("Red"));
	//creatureList.push_back((new Ogre())->AddPrefix("Blue"));
	//creatureList.push_back(new Snake());

	std::cout << "Welcome to the Monster Mash Arena!\n\n";

	std::cout << "Our contestants tonight are:\n\n";
	for (Creature* creature : creatureList)
	{
		sleep(1.5f);
		std::cout << creature->GetName() << "\n";		
	}

	for (int i = 0; i < 3; i++)
	{
		std::cout << ".";
		sleep(0.5f);
	}

	std::cout << "Fight!\n\n";

	while (true)
	{
		int liveCount = 0;
		Creature* lastAlive = nullptr;

		std::cout << "Round summary:\n";
		std::cout << "Name:\t\t\t\t\tStatus:\t\tHealth\t\t\n";

		std::vector<Creature*> creatureListCopy = creatureList;
		for (Creature* creature : creatureListCopy)
		{
			std::cout << creature->GetName() << "\t\t";
			if (creature->IsDead())
			{
				std::cout << "dead\t\t";
			}
			else
			{
				std::cout << "alive\t\t";
			}
			std::cout << creature->GetHealth() << "\n";
		}
		creatureList = creatureListCopy;

		std::cout << "\n\n";

		sleep(2.0f);

		for (Creature* creature : creatureList)
		{
			if (!creature->IsDead())
			{
				creature->Update(creatureList);
				sleep(3.5f);
				std::cout << "\n";
				liveCount++;
				lastAlive = creature;
			}			
		}

		if (liveCount == 1 && lastAlive)
		{
			std::cout << "\nAll other creatures are dead, " << lastAlive->GetName() << " is the WINNER!\n\n";
			std::cout << "Thanks for watching!\n\n";
			break;
		}
	}

	system("PAUSE");

    return 0;
}

