#include "Connection.h"

Connection::Connection(int fromIndex, int toIndex)
	: m_FromIndex(fromIndex),
	m_ToIndex(toIndex)
{

}

Connection::~Connection()
{

}

void Connection::SetWeight(double weight)
{
	m_Weight = weight;
}

void Connection::OffsetWeight(double offset)
{
	m_Weight += offset;
}

double Connection::GetWeight()
{
	return m_Weight;
}

int Connection::GetFrom()
{
	return m_FromIndex;
}

int Connection::GetTo()
{
	return m_ToIndex;
}