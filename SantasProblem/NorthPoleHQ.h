#pragma once
#include"Elf.h"
#include"Santa.h"
#include"Reindeer.h"
#include<vector>

class NorthPoleHQ
{
public:
	NorthPoleHQ();
	NorthPoleHQ(int numberOfElves, int numberOfReindeers);
	virtual ~NorthPoleHQ();

protected:
	std::vector<Elf*> elves;
	std::vector<Reindeer*> reindeers;
	Santa* santa;
};

