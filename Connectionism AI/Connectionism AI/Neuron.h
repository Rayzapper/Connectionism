#ifndef RAYZAPPER_NEURON_H
#define RAYZAPPER_NEURON_H

enum NeuronType
{
	Identity,
	Bias,
	Sigmoid
};

class Neuron
{
public:
	Neuron(NeuronType type);
	~Neuron();
private:
	NeuronType m_Type;
	double m_Value;
};

#endif