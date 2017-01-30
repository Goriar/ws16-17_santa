#pragma once
#include "Worker.h"
class Elf :
	public Worker
{
public:
	Elf();
	virtual ~Elf();
	void makePresents();
	void work(void);

	enum Status { MAKING_PRESENTS, CANT_MAKE_PRESENT, MAKING_PRESENTS_WITH_SANTA };

protected:
	static int id_inc;
	int id = id_inc++;
};

