#ifndef RAYZAPPER_EXAMPLE_H
#define RAYZAPPER_EXAMPLE_H

#include <vector>
#include <string>

using namespace std;

class Example
{
public:
	Example();
	~Example();
	void AddInputValue(double value);
	void AddOutputValue(double value);
	void SetSentence(string text);
	vector<double> GetInputValues();
	vector<double> GetOutputValues();
	string GetSentence();
private:
	vector<double> m_InputValues, m_OutputValues;
	string m_Sentence;
};

#endif