#ifndef RAYZAPPER_LAYER_H
#define RAYZAPPER_LAYER_H

#include <vector>
#include "Neuron.h"

using namespace std;

class Layer
{
public:
	Layer();
	~Layer();
	void AddNeuron(Neuron *neuron);
	vector<Neuron*> GetNeurons();
private:
	vector<Neuron*> m_Neurons;
};

#endif