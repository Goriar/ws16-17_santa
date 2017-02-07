#define BOOST_THREAD_PROVIDES_FUTURE
#include "NorthPoleHQ.h"
#include <cmath>
#include <boost\thread\future.hpp>

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
	m_threads.interrupt_all();
	m_threads.join_all();

	m_elves.~vector();
	m_reindeers.~vector();

	delete m_santa;
	instance = NULL;
}

NorthPoleHQ * NorthPoleHQ::getInstance()
{
	boost::mutex m;
	m.timed_lock(boost::xtime());
	if (instance == NULL) {
		NorthPoleHQ();
	}
	return instance;

}

void NorthPoleHQ::requestToSanta(Request r, const Worker *w)
{
	
	if (r == HELP_ELVES) {
		numberOfElfRequests++;
	}
	if (r == DELIVER_PRESENTS) {
		numberOfReindeerRequests++;
	}

	//m_requestMutex.lock();
	boost::unique_lock<boost::mutex> t{ m_requestMutex };
	if (numberOfReindeerRequests == m_reindeers.size()) {
		boost::future<bool> f = boost::async(boost::bind(&Santa::requestJob,m_santa,DELIVER_PRESENTS));	
		if (f.get() == true) {
			numberOfReindeerRequests = 0;
			m_santa->setStatus(Santa::WAITING_FOR_SWEET_RELEASE_OF_DEATH);
			for each (Reindeer* rnd in m_reindeers)
			{
				rnd->setStatus(Reindeer::GOING_ON_VACATION);
			}
			this->writeInHQLog("\nHQ: Present Delivery Successfull\n-------------------------------------------");
		}
		else {
			this->writeInHQLog("\nHQ: Present Delivery Failed!!\n-------------------------------------------");
		}
		
	}

	else if(numberOfElfRequests >= m_elves.size()/4) {
		boost::future<bool> f = boost::async(boost::bind(&Santa::requestJob, m_santa, HELP_ELVES));
		if (f.get()) {
			numberOfElfRequests = 0;
			m_santa->setStatus(Santa::WAITING_FOR_SWEET_RELEASE_OF_DEATH);
			for each (Elf* e in m_elves)
			{
				e->setStatus(Elf::MAKING_PRESENTS);
			}
			this->writeInHQLog("\nHQ: Santa helped Elves!\n-------------------------------------------");
		}
		else {
			this->writeInHQLog("\nHQ: Santa couldn't help Elves!!\n-------------------------------------------");
		}
	}
	//m_requestMutex.unlock();
}

void NorthPoleHQ::writeInHQLog(std::string message)
{
	//m_writeMutex.lock();
	boost::unique_lock<boost::timed_mutex> lock{ m_writeMutex,boost::try_to_lock };
	if (lock.owns_lock() || lock.try_lock_for(boost::chrono::seconds{ 2 })) {
		std::cout << message << std::endl;
	}
	//m_writeMutex.unlock();
}


void NorthPoleHQ::start() {
	for each (Reindeer* w in m_reindeers)
	{
		boost::thread* t = new boost::thread(&Reindeer::work, w);
		m_threads.add_thread(t);
	}

	for each (Elf* w in m_elves)
	{
		boost::thread* t = new boost::thread(&Elf::work, w);
		m_threads.add_thread(t);
	}

	boost::thread* t = new boost::thread(&Santa::work, m_santa);
	m_threads.add_thread(t);
}

