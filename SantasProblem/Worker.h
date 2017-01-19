#pragma once
class Worker
{
public:
	Worker();
	~Worker();
	void sleep();
	void wake();

protected:
	int m_currentStatus;
};

