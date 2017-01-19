#pragma once
#include"Elf.h"
#include"Santa.h"
#include"Reindeer.h"
#include<vector>
#include<boost\thread\thread.hpp>

class NorthPoleHQ
{
public:
	NorthPoleHQ();
	NorthPoleHQ(int numberOfElves, int numberOfReindeers);
	virtual ~NorthPoleHQ();

protected:
	std::vector<Elf*> m_elves;
	std::vector<Reindeer*> m_reindeers;
	Santa* m_santa;

	boost::thread_group m_threads;

private:
	void start();
};

