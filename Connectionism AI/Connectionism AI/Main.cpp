#include <random>
#include <time.h>
#include <iostream>
#include "Layer.h"
#include "Example.h"
#include "Connection.h"

vector<Example*> examples;
vector<vector<Connection*>*> connectionLayers;
const int hiddenLayerAmount = 1;
const double learningSpeed = 0.02;
Layer layers[hiddenLayerAmount + 2];
int layerSizes[hiddenLayerAmount + 2] = { 25, 8, 4 }, totalEpochs = 0;

void Cleanup()
{
	for each (Example *e in examples)
	{
		delete e;
	}
	examples.clear();
	for each (vector<Connection*> *v in connectionLayers)
	{
		for each (Connection *c in *v)
		{
			delete c;
		}
		v->clear();
		delete v;
	}
	connectionLayers.clear();
}

void Setup()
{
	for (size_t i = 0; i < layerSizes[0]; i++)
	{
		Neuron *neuron = new Neuron(Identity);
		neuron->SetInput(0.0);
		layers[0].AddNeuron(neuron);
	}
	layers[0].AddNeuron(new Neuron(Bias));

	for (size_t l = 0; l < hiddenLayerAmount; l++)
	{
		for (size_t i = 0; i < layerSizes[l + 1]; i++)
		{
			Neuron *neuron = new Neuron(Sigmoid);
			neuron->SetInput(0.0);
			layers[l + 1].AddNeuron(neuron);
		}
		layers[l + 1].AddNeuron(new Neuron(Bias));
	}

	for (size_t i = 0; i < layerSizes[hiddenLayerAmount + 1]; i++)
	{
		Neuron *neuron = new Neuron(Sigmoid);
		neuron->SetInput(0.0);
		layers[hiddenLayerAmount + 1].AddNeuron(neuron);
	}

	for (size_t i = 0; i < hiddenLayerAmount + 1; i++)
	{
		vector<Connection*> *connections = new vector<Connection*>;
		for (int j = 0; j < layers[i].GetNeurons().size(); j++)
		{
			for (int k = 0; k < layers[i + 1].GetNeurons().size(); k++)
			{
				Connection *connection = new Connection(j, k);
				connection->SetWeight((((double)rand() / RAND_MAX) * 2) - 1);
				connections->push_back(connection);
			}
		}
		connectionLayers.push_back(connections);
	}

	/*for (size_t i = 0; i < layerSizes[0]; i++)
	{
		Neuron *neuron = new Neuron(Identity);
		layers[0].AddNeuron(neuron);
	}
	layers[0].AddNeuron(new Neuron(Bias));

	for (size_t l = 0; l < hiddenLayerAmount; l++)
	{
		for (size_t i = 0; i < layerSizes[l + 1]; i++)
		{
			Neuron *neuron = new Neuron(Sigmoid);
			layers[l + 1].AddNeuron(neuron);
			for (size_t i = 0; i < layers[l].GetNeurons().size(); i++)
			{
				connections.push_back(((double)rand() / RAND_MAX) * 2 - 1);
			}
		}
		layers[l + 1].AddNeuron(new Neuron(Bias));
		for (size_t i = 0; i < layers[l].GetNeurons().size(); i++)
		{
			connections.push_back(((double)rand() / RAND_MAX) * 2 - 1);
		}
	}

	for (size_t i = 0; i < layerSizes[hiddenLayerAmount + 1]; i++)
	{
		Neuron *neuron = new Neuron(Sigmoid);
		layers[hiddenLayerAmount + 1].AddNeuron(neuron);
		for (size_t i = 0; i < layers[hiddenLayerAmount].GetNeurons().size(); i++)
		{
			connections.push_back(((double)rand() / RAND_MAX) * 2 - 1);
		}
	}*/
}

vector<double> CalculateInputValues(string sentence)
{
	vector<double> values;

	int letterCount[25] =
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	};

	for each (char c in sentence)
	{
		if (c == 'a' || c == 'å' || c == 'ä' || c == 'A' || c == 'Ä' || c == 'Å') letterCount[0]++;
		else if (c == 'b' || c == 'B') letterCount[1]++;
		else if (c == 'c' || c == 'C') letterCount[2]++;
		else if (c == 'd' || c == 'D') letterCount[3]++;
		else if (c == 'e' || c == 'é' || c == 'E' || c == 'É') letterCount[4]++;
		else if (c == 'f' || c == 'F') letterCount[5]++;
		else if (c == 'g' || c == 'G') letterCount[6]++;
		else if (c == 'h' || c == 'H') letterCount[7]++;
		else if (c == 'i' || c == 'I') letterCount[8]++;
		else if (c == 'j' || c == 'J') letterCount[9]++;
		else if (c == 'k' || c == 'K') letterCount[10]++;
		else if (c == 'l' || c == 'L') letterCount[11]++;
		else if (c == 'm' || c == 'M') letterCount[12]++;
		else if (c == 'n' || c == 'N') letterCount[13]++;
		else if (c == 'o' || c == 'ö' || c == 'O' || c == 'Ö') letterCount[14]++;
		else if (c == 'p' || c == 'P') letterCount[15]++;
		else if (c == 'q' || c == 'Q') letterCount[16]++;
		else if (c == 'r' || c == 'R') letterCount[17]++;
		else if (c == 's' || c == 'S') letterCount[18]++;
		else if (c == 't' || c == 'T') letterCount[19]++;
		else if (c == 'u' || c == 'ü' || c == 'U' || c == 'Ü') letterCount[20]++;
		else if (c == 'v' || c == 'w' || c == 'V' || c == 'W') letterCount[21]++;
		else if (c == 'x' || c == 'X') letterCount[22]++;
		else if (c == 'y' || c == 'Y') letterCount[23]++;
		else if (c == 'z' || c == 'Z') letterCount[24]++;
	}

	if (sentence.size() > 0)
	{
		for (size_t i = 0; i < layerSizes[0]; i++)
		{
			values.push_back((double)letterCount[i] / sentence.size());
		}
	}

	return values;
}

void CreateExample(string sentence, int language)
{
	Example *example = new Example();

	example->SetSentence(sentence);
	for (int i = 0; i < language; i++)
	{
		example->AddOutputValue(0.0);
	}
	example->AddOutputValue(1.0);
	for (int i = 0; i < layerSizes[hiddenLayerAmount + 1] - 1 - language; i++)
	{
		example->AddOutputValue(0.0);
	}

	vector<double> inputValues = CalculateInputValues(sentence);

	for (size_t i = 0; i < layerSizes[0]; i++)
	{
		example->AddInputValue(inputValues[i]);
	}

	examples.push_back(example);
}

void SetupExamples()
{
	CreateExample("A rose by any other name would smell as sweet.", 0);
	CreateExample("Den som inte vill arbeta i värmen, han får hungra i kölden.", 1);
	CreateExample("Alle wollen in den Himmel, aber niemand will sterben.", 2);
	CreateExample("Le livre est l'opium de l'Occident.", 3);
	CreateExample("Genius is one percent inspiration and ninety-nine percent perspiration.", 0);
	CreateExample("Den djupaste brunnen kan också tömmas.", 1);
	CreateExample("Manche Laster lassen mit dem Alter nach, andere werden ärger.", 2);
	CreateExample("Plus l'offenseur m'est cher, plus je ressens l'injure.", 3);
	CreateExample("I have always depended on the kindness of strangers.", 0);
	CreateExample("I brist på höns tar räven kråkor.", 1);
	CreateExample("Der Dirigent ist als Magier am Werk. Er hält seine Hände beschwörend hoch, bis die Musik wetterleuchtet und donnert.", 2);
	CreateExample("Tout commence en mystique et finit en politique.", 3);
	CreateExample("What we've got here is failure to communicate. Some men you just can't reach.", 0);
	CreateExample("Bättre ensam än i dåligt sällskap.", 1);
	CreateExample("Mit einer geballten Faust kann man keine Hände schütteln.", 2);
	CreateExample("On nous apprend à vivre quand la vie est passée.", 3);
}

vector<double> Propagate(vector<double> inputVector)
{
	vector<double> outputVector;

	for (size_t i = 0; i < layerSizes[0]; i++)
	{
		layers[0].GetNeurons()[i]->SetInput(inputVector[i]);
	}

	for (size_t i = 0; i < connectionLayers.size(); i++)
	{
		for each (Neuron *n in layers[i + 1].GetNeurons())
		{
			n->SetInput(0.0);
		}
		vector<Connection*> *connections = connectionLayers[i];
		for each (Connection *c in *connections)
		{
			layers[i + 1].GetNeurons()[c->GetTo()]->OffsetInput(layers[i].GetNeurons()[c->GetFrom()]->GetOutput() * c->GetWeight());
		}
	}

	for each (Neuron *n in layers[hiddenLayerAmount + 1].GetNeurons())
	{
		outputVector.push_back(n->GetOutput());
	}

	/*size_t connectionIterator = 0;

	for (size_t i = 0; i < layerSizes[0]; i++)
	{
		layers[0].GetNeurons()[i]->SetInput(inputVector[i]);
	}

	for (size_t l = 0; l < hiddenLayerAmount; l++)
	{
		for (size_t i = 0; i < layerSizes[l + 1]; i++)
		{
			double input = 0.0;
			for (size_t j = 0; j < layerSizes[l]; j++)
			{
				input += layers[l].GetNeurons()[j]->GetOutput() * connections[connectionIterator];
				connectionIterator++;
			}
			layers[l + 1].GetNeurons()[i]->SetInput(input);
		}
	}

	for (size_t i = 0; i < layerSizes[hiddenLayerAmount + 1]; i++)
	{
		double input = 0.0;
		for (size_t j = 0; j < layerSizes[hiddenLayerAmount]; j++)
		{
			input += layers[hiddenLayerAmount].GetNeurons()[j]->GetOutput() * connections[connectionIterator];
			connectionIterator++;
		}
		layers[hiddenLayerAmount + 1].GetNeurons()[i]->SetInput(input);

		outputVector.push_back(layers[hiddenLayerAmount + 1].GetNeurons()[i]->GetOutput());
	}*/

	return outputVector;
}

void BackPropagate(vector<double> errorVector)
{
	for (size_t i = 0; i < layers[hiddenLayerAmount + 1].GetNeurons().size(); i++)
	{
		Neuron *n = layers[hiddenLayerAmount + 1].GetNeurons()[i];
		n->SetDelta(n->GetDerivative() * errorVector[i]);
	}
	for (size_t i = 0; i < connectionLayers[hiddenLayerAmount]->size(); i++)
	{
		Connection *c = connectionLayers[hiddenLayerAmount]->at(i);
		c->OffsetWeight(learningSpeed * layers[hiddenLayerAmount].GetNeurons()[c->GetFrom()]->GetOutput() * layers[hiddenLayerAmount + 1].GetNeurons()[c->GetTo()]->GetDelta());
	}

	for (int i = hiddenLayerAmount; i > 0; i--)
	{
		size_t connectionIterator = 0;
		for (size_t j = 0; j < layers[i].GetNeurons().size(); j++)
		{
			Neuron *n = layers[i].GetNeurons()[j];
			double d = 0.0;
			for (size_t k = 0; k < layers[i + 1].GetNeurons().size(); k++)
			{
				Connection *c = connectionLayers[i]->at(connectionIterator);
				d += c->GetWeight() * layers[i + 1].GetNeurons()[k]->GetDelta();
				connectionIterator++;
			}
			n->SetDelta(n->GetDerivative() * d);
		}
		for (size_t j = 0; j < connectionLayers[i - 1]->size(); j++)
		{
			Connection *c = connectionLayers[i - 1]->at(j);
			c->OffsetWeight(learningSpeed * layers[i - 1].GetNeurons()[c->GetFrom()]->GetOutput() * layers[i].GetNeurons()[c->GetTo()]->GetDelta());
		}
	}

	/*size_t connectionBackIterator = connections.size() - 1, connectionBackIterator2 = connections.size() - 1;

	for (int i = layerSizes[hiddenLayerAmount + 1] - 1; i >= 0; i--)
	{
		double d = layers[hiddenLayerAmount + 1].GetNeurons()[i]->GetDerivative() * errorVector[i];
		for (int j = layerSizes[hiddenLayerAmount] - 1; j >= 0; j--)
		{
			connections[connectionBackIterator] += (learningSpeed * layers[hiddenLayerAmount].GetNeurons()[j]->GetOutput() * d);
			connectionBackIterator--;
		}
	}

	for (int l = hiddenLayerAmount; l > 0; l--)
	{
		for (int i = layerSizes[l] - 1; i >= 0; i--)
		{
			double d = 0;
			for (int j = layerSizes[l + 1] - 1; j >= 0; j--)
			{
				d += layers[l].GetNeurons()[i]->GetDerivative() * connections[connectionBackIterator2] * layers[l + 1].GetNeurons()[j]->GetDerivative() * errorVector[j];
				connectionBackIterator2 -= layerSizes[l + 1];
			}
			connectionBackIterator2 += layerSizes[l + 1] * layerSizes[l + 1] - 1;
			for (int j = layerSizes[l - 1] - 1; j >= 0; j--)
			{
				connections[connectionBackIterator] += (learningSpeed * layers[l - 1].GetNeurons()[j]->GetOutput() * d);
				connectionBackIterator--;
			}
		}
	}*/
}

void Train(int epochs)
{
	vector<Example*> trainingExamples;
	trainingExamples.push_back(examples[0]);
	trainingExamples.push_back(examples[1]);
	trainingExamples.push_back(examples[2]);
	trainingExamples.push_back(examples[3]);
	trainingExamples.push_back(examples[4]);
	trainingExamples.push_back(examples[5]);
	trainingExamples.push_back(examples[6]);
	trainingExamples.push_back(examples[7]);
	trainingExamples.push_back(examples[8]);
	trainingExamples.push_back(examples[9]);
	trainingExamples.push_back(examples[10]);
	trainingExamples.push_back(examples[11]);

	for (size_t i = 0; i < epochs; i++)
	{
		double minError = 99.0, maxError = 0.0, averageError = 0.0;
		for each (Example *e in trainingExamples)
		{
			vector<double> errorVector, outputVector;
			outputVector = Propagate(e->GetInputValues());
			for (size_t j = 0; j < layerSizes[hiddenLayerAmount + 1]; j++)
			{
				errorVector.push_back(e->GetOutputValues()[j] - outputVector[j]);
			}
			BackPropagate(errorVector);
			double errorValue = errorVector[0] * errorVector[0] + errorVector[1] * errorVector[1] + errorVector[2] * errorVector[2] + errorVector[3] * errorVector[3];
			averageError += errorValue;
			if (errorValue > maxError) maxError = errorValue;
			if (errorValue < minError) minError = errorValue;
		}
		if (totalEpochs % 100 == 0 && totalEpochs != 0)
		{
			averageError /= trainingExamples.size();
			cout << "----- epoch " << totalEpochs << " -----" << endl;
			cout << "Min Error: " << minError << endl;
			cout << "Max Error: " << maxError << endl;
			cout << "Average Error: " << averageError << endl;
		}
		totalEpochs++;
	}
}

void Test(string text)
{
	vector<double> output = Propagate(CalculateInputValues(text));
	cout << "English: " << output[0] << endl;
	cout << "Swedish: " << output[1] << endl;
	cout << "German: " << output[2] << endl;
	cout << "French: " << output[3] << endl;
}

void TestExample(Example *example)
{
	vector<double> output = Propagate(CalculateInputValues(example->GetSentence()));
	cout << "English: " << output[0] << " - " << example->GetOutputValues()[0] << endl;
	cout << "Swedish: " << output[1] << " - " << example->GetOutputValues()[1] << endl;
	cout << "German: " << output[2] << " - " << example->GetOutputValues()[2] << endl;
	cout << "French: " << output[3] << " - " << example->GetOutputValues()[3] << endl;
}

int main()
{
	srand(time(NULL));

	Setup();
	SetupExamples();

	

	int input = -1;

	while (input != 0)
	{
		cin >> input;
		Train(input);

		cout << '"' << examples[8]->GetSentence() << '"' << endl;
		TestExample(examples[12]);
		cout << '"' << examples[9]->GetSentence() << '"' << endl;
		TestExample(examples[13]);
		cout << '"' << examples[10]->GetSentence() << '"' << endl;
		TestExample(examples[14]);
		cout << '"' << examples[11]->GetSentence() << '"' << endl;
		TestExample(examples[15]);
	}

	Cleanup();
	return 0;
}