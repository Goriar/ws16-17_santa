
#include "NorthPoleHQ.h"
#include <cmath>

NorthPoleHQ* NorthPoleHQ::instance = NULL;
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
	numberOfElfRequests = 0;
	numberOfReindeerRequests = 0;
	instance = this;
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
	numberOfElfRequests = 0;
	numberOfReindeerRequests = 0;
	instance = this;
	start();
}

NorthPoleHQ::~NorthPoleHQ()
{
	m_threads.join_all();

	m_elves.~vector();
	m_reindeers.~vector();

	delete m_santa;
}

NorthPoleHQ * NorthPoleHQ::getInstance()
{
	if (instance == NULL) {
		NorthPoleHQ();
	}
	return instance;
}

void NorthPoleHQ::requestToSanta(Request r)
{
	if (r == HELP_ELVES) {
		numberOfElfRequests++;
	}
	if (r == DELIVER_PRESENTS) {
		numberOfReindeerRequests++;
	}

	while (numberOfReindeerRequests == sizeof(m_reindeers)) {
		mutex.lock();
		m_santa->requestJob(r);
		numberOfReindeerRequests = 0;
		for each (Reindeer* rnd in m_reindeers)
		{
			rnd->setStatus(Reindeer::GOING_ON_VACATION);
		}
		mutex.unlock();
	}

	while (numberOfElfRequests >= sizeof(m_elves)/4) {
		mutex.lock();
		m_santa->requestJob(r);
		numberOfElfRequests = 0;
		for each (Elf* e in m_elves)
		{
			e->setStatus(Elf::MAKING_PRESENTS);
		}
		mutex.unlock();
	}
}

void NorthPoleHQ::start() {
	for each (Reindeer* w in m_reindeers)
	{
		boost::thread t = boost::thread(&Reindeer::work, w);
		m_threads.add_thread(&t);
	}

	for each (Elf* w in m_elves)
	{
		boost::thread t = boost::thread(&Elf::work, w);
		m_threads.add_thread(&t);
	}

	boost::thread t = boost::thread(&Santa::work, m_santa);
	m_threads.add_thread(&t);
}

