#ifndef RAYZAPPER_CONNECTION_H
#define RAYZAPPER_CONNECTION_H

class Connection
{
public:
	Connection(int fromIndex, int toIndex);
	~Connection();
	void SetWeight(double weight);
	void OffsetWeight(double offset);
	double GetWeight();
	int GetFrom();
	int GetTo();
private:
	double m_Weight = 0.0;
	int m_FromIndex, m_ToIndex;
};

#endif