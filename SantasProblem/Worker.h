#pragma once
class Worker
{
public:
	Worker();
	~Worker();
	virtual void work(void) = 0;

protected:
	int m_currentStatus;
	bool m_markedForDeletion = false;
};

