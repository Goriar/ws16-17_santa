
#include "Santa.h"
#include "NorthPoleHQ.h"
#include <stdio.h>
#include<boost\thread\thread.hpp>
#include<boost\chrono\chrono.hpp>


Santa::Santa()
{
	this->m_currentStatus = WAITING_FOR_SWEET_RELEASE_OF_DEATH;
}


Santa::~Santa()
{
}

void Santa::deliverPresents() {
	std::string message =  "Santa: Bringing joy to the world...except me\n";
	NorthPoleHQ::getInstance()->writeInHQLog(message);
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
}

void Santa::helpElves() {

	NorthPoleHQ* hq = NorthPoleHQ::getInstance();

	std::string message = "Santa: Making presents for incompetent elves";
	hq->writeInHQLog(message);
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	message = "Santa: Done..going to sleep";
	hq->writeInHQLog(message);
	m_currentStatus = WAITING_FOR_SWEET_RELEASE_OF_DEATH;
}

void Santa::strapInReindeers() {

	NorthPoleHQ* hq = NorthPoleHQ::getInstance();
	std::string message = "Santa: Strapping in Reindeers";
	hq->writeInHQLog(message);
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	deliverPresents();
	message = "Santa: Done..going to sleep";
	hq->writeInHQLog(message);
	m_currentStatus = WAITING_FOR_SWEET_RELEASE_OF_DEATH;
}


void Santa::work(void) {
	
	try {
		while (!m_markedForDeletion) {			
			switch (m_currentStatus)
			{
			case DELIVERING_TO_THE_UNGRATEFUL:
				deliverPresents();
				break;
			case HELPING_INCOMPETENT_ELVES:
				helpElves();
				break;
			case PREPING_SLEIGH_PLUS_CRYING:
				strapInReindeers();
				break;
			default:
				break;
			}
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted& ex) {
		m_markedForDeletion = true;
	}
}

bool Santa::requestJob(int r)
{
	if (r == NorthPoleHQ::HELP_ELVES) {
		helpElves();
		return true;
	}
	if (r == NorthPoleHQ::DELIVER_PRESENTS) {
		strapInReindeers();
		return true;
	}

	return false;
}
