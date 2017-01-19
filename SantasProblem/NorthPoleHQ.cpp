#include "stdafx.h"
#include "NorthPoleHQ.h"
#include <cmath>


NorthPoleHQ::NorthPoleHQ()
{
	for (int i = 0; i < 12; i++)
	{
		if (i <= 8) {
			m_reindeers.push_back(new Reindeer());
		}
		m_elves.push_back(new Elf());
	}

	m_santa = new Santa();
	start();
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
			m_reindeers.push_back(new Reindeer());
		}
		if (i < numberOfElves) {
			m_elves.push_back(new Elf());
		}
	}

	m_santa = new Santa();
	start();
}

NorthPoleHQ::~NorthPoleHQ()
{
	m_threads.join_all();

	m_elves.~vector();
	m_reindeers.~vector();

	delete m_santa;
}

void NorthPoleHQ::start() {
	for each (Reindeer* w in m_reindeers)
	{
		m_threads.create_thread(w->work);
	}

	for each (Elf* w in m_elves)
	{
		m_threads.create_thread(w->work);
	}

	m_threads.create_thread(m_santa->work);
}
