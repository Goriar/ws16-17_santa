#pragma once
#include"Worker.h"
class Santa : Worker
{
public:
	Santa();
	virtual ~Santa();
	void deliverPresents();
	void helpElves();
	void strapInReindeers();
	void work(void);

	enum Status { WAITING_FOR_SWEET_RELEASE_OF_DEATH, HELPING_INCOMPETENT_ELVES, PREPING_SLEIGH_PLUS_CRYING, DELIVERING_TO_THE_UNGRATEFUL };
protected:
	

};

