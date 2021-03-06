#pragma once
#include "Worker.h"

class Santa : public Worker
{
public:
	Santa();
	virtual ~Santa();
	void deliverPresents();
	void helpElves();
	void strapInReindeers();
	void work(void);
	bool requestJob(int r);

	enum Status { WAITING_FOR_SWEET_RELEASE_OF_DEATH, HELPING_INCOMPETENT_ELVES, PREPING_SLEIGH_PLUS_CRYING, DELIVERING_TO_THE_UNGRATEFUL };
};

