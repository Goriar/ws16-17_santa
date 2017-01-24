
#include "Worker.h"


Worker::Worker()
{
}


Worker::~Worker()
{
}

void Worker::setStatus(int s)
{
	m_currentStatus = s;
}

int Worker::getStatus()
{
	return m_currentStatus;
}
