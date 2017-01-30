#pragma once
#include<boost\thread\mutex.hpp>
class Worker
{
public:
	Worker();
	~Worker();
	virtual void work(void) = 0;

	void setStatus(int s);
	int getStatus();
protected:
	int m_currentStatus;
	bool m_markedForDeletion = false;
};

