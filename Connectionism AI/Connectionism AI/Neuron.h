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
	void SetInput(double value);
	void OffsetInput(double offset);
	void SetDelta(double delta);
	double GetInput();
	double GetDelta();
	double GetOutput();
	double GetDerivative();
private:
	NeuronType m_Type;
	double m_Value = 0.0, m_Delta;
};

#endif