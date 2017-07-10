#include <iostream>
#include <random>
#include <vector>

using namespace std;

// Constants
int TRAINING_SAMPLES = 1000;
int TESTING_SAMPLES = 1000;
double TRAINING_RANGE = 20;
double LEARNING_RATE = 1;

double seperationFcn(double x) {
	return 2 * x + 10;
}

int activate(double input) {
	if (input > 0) {
		return 1;
	}
	else {
		return -1;
	}
}

double genRnd(double min, double max) {
	random_device rd;  // Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(min, max);

	return dis(gen);
}

class Neuron {
	private:
		double w0;
		double w1;
		double w2;
	public:
		Neuron(double, double, double);
		double getWeight(int);
		int evaluate(double, double, double);
		void learn(double, double, double, int);
};

Neuron::Neuron(double weight0, double weight1, double weight2) {
	w0 = weight0;
	w1 = weight1;
	w2 = weight2;
}

int Neuron::evaluate(double x0, double x1, double x2) {
	return activate(x0 * w0 + x1 * w1 + x2 * w2);
}

void Neuron::learn(double x0, double x1, double x2, int correctLabel) {
	int error = correctLabel - evaluate(x0, x1, x2);
	w0 += error * x0 * LEARNING_RATE;
	w1 += error * x1 * LEARNING_RATE;
	w2 += error * x2 * LEARNING_RATE;
}

double Neuron::getWeight(int i) {
	if (i == 0) {
		return w0;
	}
	else if (i == 1) {
		return w1;
	}
	else {
		return w2;
	}
}

int main() {
	
	Neuron neuron(1, 1, 1);

	// Training the neuron
	cout << "Training Phase" << endl;
	for (int i = 0; i < TRAINING_SAMPLES; i++) {
		// Generate sample data-point
		double x0 = genRnd(-TRAINING_RANGE / 2, TRAINING_RANGE / 2);
		double x1 = genRnd(-TRAINING_RANGE / 2, TRAINING_RANGE / 2);
		double x2 = 1;
		int label = -1;

		if (x1 > seperationFcn(x0)) {
			label = 1;
		}

		//cout << "x0: " << x0 << "  x1: " << x1 << "  label: " << label << endl;
		cout << "w0: " << neuron.getWeight(0) << "  w1: " << neuron.getWeight(1) << endl;

		// Change weights based on outcome
		neuron.learn(x0, x1, x2, label);
	}

	// Testing the neuron
	cout << endl << "Testing Phase" << endl;
	int correctTests = 0;

	for (int i = 0; i < TESTING_SAMPLES; i++) {
		// Generate sample data-point
		double x0 = genRnd(-TRAINING_RANGE / 2, TRAINING_RANGE / 2);
		double x1 = genRnd(-TRAINING_RANGE / 2, TRAINING_RANGE / 2);
		double x2 = 1;
		int label = -1;

		if (x1 > seperationFcn(x0)) {
			label = 1;
		}

		int predictedLabel = neuron.evaluate(x0, x1, x2);
		bool correct = false;

		if (predictedLabel == label) {
			correct = true;
			correctTests++;
		}

		//cout << "x0: " << x0 << "  x1: " << x1 << "  label: " << label << "  Predicted: " << predictedLabel << "  Correct? " << correct << endl;
	}

	cout << endl << "Tests got right: " << correctTests / (double) TESTING_SAMPLES * 100 << " %" << endl;

	cin.get();
	return 0;
}