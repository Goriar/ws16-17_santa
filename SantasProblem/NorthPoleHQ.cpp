#include "stdafx.h"
#include "NorthPoleHQ.h"
#include <cmath>


NorthPoleHQ::NorthPoleHQ()
{
	for (int i = 0; i < 12; i++)
	{
		if (i <= 8) {
			reindeers.push_back(new Reindeer());
		}
		elves.push_back(new Elf());
	}
}

NorthPoleHQ::NorthPoleHQ(int numberOfElves, int numberOfReindeers) {
	if (numberOfElves == 0) {
		numberOfElves = 12;
	}

	if (numberOfReindeers == 0) {
		numberOfReindeers = 9;
	}

	for (int i = 0; i < fmaxl(numberOfElves,numberOfReindeers); i++)
	{
		if (i < numberOfReindeers) {
			reindeers.push_back(new Reindeer());
		}
		if (i < numberOfElves) {
			elves.push_back(new Elf());
		}
	}
}

NorthPoleHQ::~NorthPoleHQ()
{
}
