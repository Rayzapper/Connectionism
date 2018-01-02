#include "Neuron.h"
#include <math.h>

static const double e = 2.71828182845904523536;

Neuron::Neuron(NeuronType type)
	: m_Type(type)
{
	
}

Neuron::~Neuron()
{

}

void Neuron::SetInput(double value)
{
	m_Value = value;
}

void Neuron::OffsetInput(double offset)
{
	m_Value += offset;
}

void Neuron::SetDelta(double delta)
{
	m_Delta = delta;
}

double Neuron::GetInput()
{
	return m_Value;
}

double Neuron::GetDelta()
{
	return m_Delta;
}

double Neuron::GetOutput()
{
	double output = 0.0;

	if (m_Type == Identity)
	{
		output = m_Value;
	}
	else if (m_Type == Sigmoid)
	{
		output = 1 / (1 + pow(e, -m_Value));
	}
	else
	{
		output = -2.0;
	}

	return output;
}

double Neuron::GetDerivative()
{
	double derivative = 0.0;

	if (m_Type == Identity)
	{
		derivative = 1.0;
	}
	else if (m_Type == Sigmoid)
	{
		derivative = GetOutput() * (1 - GetOutput());
	}
	else
	{
		derivative = 0.0;
	}

	return derivative;
}