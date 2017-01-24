// SantasProblem.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include "NorthPoleHQ.h"
#include <stdio.h>


int main()
{
	NorthPoleHQ *hq = new NorthPoleHQ();
	std::string s;
	std::cin >> s;
	delete hq;
    return 0;
}

