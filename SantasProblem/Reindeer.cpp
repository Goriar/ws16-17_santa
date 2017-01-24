
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
	std::cout << "Reindeer " << id << ": Going on Vacation!\n";
	int travelTime = rand() % 10 + 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(travelTime));
	std::cout << "Reindeer " << id << ": Aaah, that's the life!\n";
	int vacationTime = rand() % 10 + 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(travelTime));
	m_currentStatus = RETURNING_HOME;
}

void Reindeer::returnToNorthPole() {
	
	std::cout << "Reindeer " << id << ": Returning to home base!\n";
	int travelTime = rand() % 10 + 1;
	boost::this_thread::sleep_for(boost::chrono::seconds(travelTime));
	NorthPoleHQ::getInstance()->requestToSanta(NorthPoleHQ::DELIVER_PRESENTS);
	std::cout << "Reindeer " << id << ": Waiting in stable!\n";
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

