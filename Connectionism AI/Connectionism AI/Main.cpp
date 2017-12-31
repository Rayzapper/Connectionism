#include <random>
#include <time.h>
#include <iostream>
#include "Layer.h"
#include "Example.h"

Layer inputLayer, hiddenLayer1, outputLayer;
vector<double> connections;
vector<Example*> examples;

void Setup()
{
	for (size_t i = 0; i < 29; i++)
	{
		Neuron *neuron = new Neuron(Identity);
		inputLayer.AddNeuron(neuron);
	}
	inputLayer.AddNeuron(new Neuron(Bias));

	for (size_t i = 0; i < 10; i++)
	{
		Neuron *neuron = new Neuron(Sigmoid);
		hiddenLayer1.AddNeuron(neuron);
		for each (Neuron *n in inputLayer.GetNeurons())
		{
			connections.push_back(((double)rand() / RAND_MAX) * 2 - 1);
		}
	}
	hiddenLayer1.AddNeuron(new Neuron(Bias));
	for each (Neuron *n in inputLayer.GetNeurons())
	{
		connections.push_back(((double)rand() / RAND_MAX) * 2 - 1);
	}

	for (size_t i = 0; i < 4; i++)
	{
		Neuron *neuron = new Neuron(Sigmoid);
		outputLayer.AddNeuron(neuron);
		for each (Neuron *n in hiddenLayer1.GetNeurons())
		{
			connections.push_back(((double)rand() / RAND_MAX) * 2 - 1);
		}
	}
}

void CreateExample(string sentence, int language)
{
	Example *example = new Example();

	example->SetSentence(sentence);
	if (language == 0)
	{
		example->AddOutputValue(1);
		example->AddOutputValue(0);
		example->AddOutputValue(0);
		example->AddOutputValue(0);
	}
	else if (language == 1)
	{
		example->AddOutputValue(0);
		example->AddOutputValue(1);
		example->AddOutputValue(0);
		example->AddOutputValue(0);
	}
	else if (language == 2)
	{
		example->AddOutputValue(0);
		example->AddOutputValue(0);
		example->AddOutputValue(1);
		example->AddOutputValue(0);
	}
	else
	{
		example->AddOutputValue(0);
		example->AddOutputValue(0);
		example->AddOutputValue(0);
		example->AddOutputValue(1);
	}

	int letterCount[29];

	for each (char c in sentence)
	{
		if (c == 'a') letterCount[0]++;
		else if (c == 'b') letterCount[1]++;
		else if (c == 'c') letterCount[2]++;
		else if (c == 'd') letterCount[3]++;
		else if (c == 'e') letterCount[4]++;
		else if (c == 'f') letterCount[5]++;
		else if (c == 'g') letterCount[6]++;
		else if (c == 'h') letterCount[7]++;
		else if (c == 'i') letterCount[8]++;
		else if (c == 'j') letterCount[9]++;
		else if (c == 'k') letterCount[10]++;
		else if (c == 'l') letterCount[11]++;
		else if (c == 'm') letterCount[12]++;
		else if (c == 'n') letterCount[13]++;
		else if (c == 'o') letterCount[14]++;
		else if (c == 'p') letterCount[15]++;
		else if (c == 'q') letterCount[16]++;
		else if (c == 'r') letterCount[17]++;
		else if (c == 's') letterCount[18]++;
		else if (c == 't') letterCount[19]++;
		else if (c == 'u') letterCount[20]++;
		else if (c == 'v') letterCount[21]++;
		else if (c == 'w') letterCount[22]++;
		else if (c == 'x') letterCount[23]++;
		else if (c == 'y') letterCount[24]++;
		else if (c == 'z') letterCount[25]++;
		else if (c == 'å') letterCount[26]++;
		else if (c == 'ä') letterCount[27]++;
		else if (c == 'ö') letterCount[28]++;
	}

	for (size_t i = 0; i < 29; i++)
	{
		example->AddInputValue(letterCount[i] / sentence.size());
	}
}

void SetupExamples()
{
	CreateExample("A rose by any other name would smell as sweet.", 0);
	CreateExample("Den som inte vill arbeta i värmen, han får hungra i kölden.", 1);
	CreateExample("Alle wollen in den Himmel, aber niemand will sterben.", 2);
	CreateExample("Le livre est l'opium de l'Occident.", 3);
}

void Cleanup()
{

}

int main()
{
	srand(time(NULL));

	Setup();

	

	Cleanup();
	return 0;
}