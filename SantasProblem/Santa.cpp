
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
	std::cout << "Santa: Bringing joy to the world...except me \n";
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	m_currentStatus = WAITING_FOR_SWEET_RELEASE_OF_DEATH;
}

void Santa::helpElves() {

	std::cout << "Santa: Making presents for incompetent elves \n";
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	std::cout << "Santa: Done..going to sleep \n";
	m_currentStatus = WAITING_FOR_SWEET_RELEASE_OF_DEATH;
}

void Santa::strapInReindeers() {
	std::cout << "Santa: Strapping in Reindeers \n";
	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	deliverPresents();
	std::cout << "Santa: Done..going to sleep \n";
	m_currentStatus = WAITING_FOR_SWEET_RELEASE_OF_DEATH;
}


void Santa::work(void) {
	while (true) {
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
	}
}

bool Santa::requestJob(int r)
{
	if (r == NorthPoleHQ::HELP_ELVES) {
		helpElves();
		return true;
	}
	if (r == NorthPoleHQ::DELIVER_PRESENTS) {
		deliverPresents();
		return true;
	}

	return false;
}
