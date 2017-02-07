// SantasProblem.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include "NorthPoleHQ.h"
#include <stdio.h>


int main()
{
	NorthPoleHQ *hq;
	
	std::string again = "";
	std::string stop = "";
	do{		
		again = "";
		hq = new NorthPoleHQ();
		std::cin >> stop;
		delete hq;
		std::cout << "\n Do you want to restart? yes/no\n";
		std::cin >> again;
	} while (again == "yes");
    return 0;
}

