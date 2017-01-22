#pragma once
#include"Elf.h"
#include"Santa.h"
#include"Reindeer.h"
#include<vector>
#include<boost\thread\thread.hpp>
#include <boost\thread\mutex.hpp>

class NorthPoleHQ
{
public:
	NorthPoleHQ();
	NorthPoleHQ(int numberOfElves, int numberOfReindeers);
	virtual ~NorthPoleHQ();
	enum Request{HELP_ELVES,DELIVER_PRESENTS};

	void requestToSanta(Request r);

protected:
	std::vector<Elf*> m_elves;
	std::vector<Reindeer*> m_reindeers;
	Santa* m_santa;

	boost::thread_group m_threads;

	int numberOfElfRequests;
	int numberOfReindeerRequests;

	boost::mutex mutex;

private:
	void start();
};

