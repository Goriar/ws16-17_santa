#pragma once
#include"Elf.h"
#include"Santa.h"
#include"Reindeer.h"
#include<vector>
#include<boost\thread\thread.hpp>
#include<boost\thread\scoped_thread.hpp>
#include <boost\thread\mutex.hpp>

class NorthPoleHQ
{
public:
	NorthPoleHQ();
	NorthPoleHQ(int numberOfElves, int numberOfReindeers);
	virtual ~NorthPoleHQ();
	enum Request{HELP_ELVES,DELIVER_PRESENTS};

	static NorthPoleHQ* getInstance();

	void requestToSanta(Request r, const Worker *w);
	void writeInHQLog(std::string message);
protected:
	std::vector<Elf*> m_elves;
	std::vector<Reindeer*> m_reindeers;
	
	Santa *m_santa;

	boost::thread_group m_threads;

	int numberOfElfRequests;
	int numberOfReindeerRequests;

	boost::mutex m_requestMutex;
	boost::timed_mutex m_writeMutex;


private:
	void start();
	static NorthPoleHQ* instance;
};

