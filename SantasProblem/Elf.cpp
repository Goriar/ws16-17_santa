
#include "Elf.h"
#include <cmath>
#include "NorthPoleHQ.h"
#include <stdio.h>

Elf::Elf()
{
	m_currentStatus = MAKING_PRESENTS;
}


Elf::~Elf()
{
}

void Elf::makePresents() {
	std::cout << "Elf: Making presents! Yaaaaaaay!\n";
	boost::this_thread::sleep_for(boost::chrono::seconds(5));
}

void Elf::work(void) {
	while (true) {
		switch (m_currentStatus)
		{
		case MAKING_PRESENTS:
		{
			int dice = rand() % 6;
			if (dice == 0) {
				setStatus(CANT_MAKE_PRESENT);
				NorthPoleHQ::getInstance()->requestToSanta(NorthPoleHQ::HELP_ELVES);
				std::cout << "Elf: I cant make this! Help Santaaa!\n";
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
	}
}
