#pragma once
#include "Worker.h"
class Reindeer :
	public Worker
{
public:
	Reindeer();
	virtual ~Reindeer();
	void goOnVaction();
	void returnToNorthPole();
	void deliverPresents();

	enum Status{GOING_ON_VACATION, ON_VACATION, RETURNING_HOME, WAITING_IN_STABLE, STRAPPED_IN_SLEIGH, DELIVERING_PRESENTS};

protected:
	
};

