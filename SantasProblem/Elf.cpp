
#include "Elf.h"
#include <cmath>
#include "NorthPoleHQ.h"
#include <stdio.h>

int Elf::id_inc = 0;
Elf::Elf()
{
	m_currentStatus = MAKING_PRESENTS;
}


Elf::~Elf()
{
}

void Elf::makePresents() {
	/*
	std::string message;
	std::stringstream str;
	str << "Elf" << id << ": Making presents! Yaaaaaaay!";
	message = str.str();
	NorthPoleHQ::getInstance()->writeInHQLog(message);
	*/
	boost::this_thread::sleep_for(boost::chrono::seconds(5));
}

void Elf::work(void) {
	try {
		std::stringstream str;
		srand(id);
		while (!m_markedForDeletion) {
			
			switch (m_currentStatus)
			{
			case MAKING_PRESENTS:
			{
				int dice = rand() % 6;
				if (dice == 0) {
					setStatus(CANT_MAKE_PRESENT);
					std::string message;
					str << "Elf " << id << ": I cant make this! Help Santaaa!";
					message = str.str();
					NorthPoleHQ::getInstance()->writeInHQLog(message);
					NorthPoleHQ::getInstance()->requestToSanta(NorthPoleHQ::HELP_ELVES, this);
					str.str("");
				}
				else {
					makePresents();
				}
				break;
			}
			case CANT_MAKE_PRESENT:
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
