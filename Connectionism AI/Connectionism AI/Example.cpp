#include "Example.h"

Example::Example()
{

}

Example::~Example()
{

}

void Example::AddInputValue(double value)
{
	m_InputValues.push_back(value);
}

void Example::AddOutputValue(double value)
{
	m_OutputValues.push_back(value);
}

void Example::SetSentence(string text)
{
	m_Sentence = text;
}

vector<double> Example::GetInputValues()
{
	return m_InputValues;
}

vector<double> Example::GetOutputValues()
{
	return m_OutputValues;
}

string Example::GetSentence()
{
	return m_Sentence;
}