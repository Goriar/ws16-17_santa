
#include "Reindeer.h"
#include "NorthPoleHQ.h"
#include <stdio.h>
#include <cmath>

int Reindeer::id_inc = 0;
Reindeer::Reindeer()
{
	m_currentStatus = GOING_ON_VACATION;
	deliverPresents();
}


Reindeer::~Reindeer()
{
}

void Reindeer::goOnVaction() {
	NorthPoleHQ* hq = NorthPoleHQ::getInstance();
	std::stringstream str;
	str << "Reindeer " << id << ": Going on Vacation!";
	std::string message = str.str();
	hq->writeInHQLog(message);

	int travelTime = rand() % 10 + 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(travelTime));
	
	str.str("");
	str << "Reindeer " << id << ": Having the time of my life!";
	message = str.str();
	hq->writeInHQLog(message);

	int vacationTime = rand() % 10 + 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(travelTime));
	m_currentStatus = RETURNING_HOME;
}

void Reindeer::returnToNorthPole() {
	
	NorthPoleHQ* hq = NorthPoleHQ::getInstance();
	std::stringstream str;
	str << "Reindeer " << id << ": Returning to home base!";
	std::string message = str.str();
	hq->writeInHQLog(message);

	int travelTime = rand() % 10 + 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(travelTime));

	str.str("");
	str << "Reindeer " << id << ": Waiting in stable!";
	message = str.str();
	hq->writeInHQLog(message);
	m_currentStatus = WAITING_IN_STABLE;

	NorthPoleHQ::getInstance()->requestToSanta(NorthPoleHQ::DELIVER_PRESENTS,this);
}

void Reindeer::deliverPresents() {

}

void Reindeer::work(void) {
	try {
		srand(id);
		while (!m_markedForDeletion) {
			
			switch (m_currentStatus)
			{
			case ON_VACATION:
				break;
			case GOING_ON_VACATION:
				goOnVaction();
				break;
			case RETURNING_HOME:
				returnToNorthPole();
			case WAITING_IN_STABLE:
				boost::this_thread::sleep_for(boost::chrono::seconds(1));
				break;
			case DELIVERING_PRESENTS:
				deliverPresents();
				break;
			default:
				break;
			}
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted&) {
		m_markedForDeletion = true;
	}
}

