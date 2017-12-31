#include "Layer.h"

Layer::Layer()
{

}

Layer::~Layer()
{

}

void Layer::AddNeuron(Neuron *neuron)
{
	m_Neurons.push_back(neuron);
}

vector<Neuron*> Layer::GetNeurons()
{
	return m_Neurons;
}