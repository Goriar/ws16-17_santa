
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
	
	str << "Reindeer " << id << ": Aaah, that's the life!";
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
	NorthPoleHQ::getInstance()->requestToSanta(NorthPoleHQ::DELIVER_PRESENTS);


	str << "Reindeer " << id << ": Waiting in stable!\n";
	message = str.str();
	m_currentStatus = WAITING_IN_STABLE;

}

void Reindeer::deliverPresents() {

}

void Reindeer::work(void) {
	while (true) {
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
			break;
		case DELIVERING_PRESENTS:
			deliverPresents();
			break;
		default:
			break;
		}
	}
}

