#include <iostream>
#include <vector>
#include <string>

using namespace std;

// LINEAR ALGEBRA CLASSES

class Vector {
	private:
		vector<double> values;
	public:
		Vector(int);
		void setValue(int, double);
		double getValue(int);
		int getRows();
		string toString();
};

Vector::Vector(int rows) {
	for (int i = 0; i < rows; i++) {
		values.push_back(0.0);
	}
}

void Vector::setValue(int row, double val) {
	values[row] = val;
}

double Vector::getValue(int row) {
	return values[row];
}

int Vector::getRows() {
	return values.size();
}

string Vector::toString() {
	string output;
	for (int i = 0; i < values.size(); i++) {
		output += to_string(this->getValue(i)) + "\n";
	}
	return output;
}

class Matrix {
	private:
		vector< vector<double> > rows;
	public:
		Matrix(int, int);
		Matrix(int, int, double);
		void setValue(int, int, double);
		double getValue(int, int);
		int getRows();
		int getCols();
		string toString();
};

Matrix::Matrix(int Nrows, int Ncols) {
	for (int i = 0; i < Nrows; i++) {
		vector<double> row(Ncols, 0.0);
		rows.push_back(row);
	}
}

Matrix::Matrix(int Nrows, int Ncols, double defaultVal) {
	for (int i = 0; i < Nrows; i++) {
		vector<double> row(Ncols, defaultVal);
		rows.push_back(row);
	}
}

void Matrix::setValue(int row, int col, double val) {
	rows[row][col] = val;
}

double Matrix::getValue(int row, int col) {
	return rows.at(row).at(col);
}

int Matrix::getRows() {
	return rows.size();
}

int Matrix::getCols() {
	return rows[0].size();
}

string Matrix::toString() {
	string output;
	for (int i = 0; i < rows.size(); i++) {
		for (int j = 0; j < rows[i].size(); j++) {
			output += to_string(this->getValue(i, j)) + " ";
		}
		output += '\n';
	}
	return output;
}

Vector operator* (Matrix& matrix, Vector& vector) {
	Vector result(matrix.getRows());
	for (int i = 0; i < result.getRows(); i++) {
		double rowValue = 0.0;
		for (int j = 0; j < vector.getRows(); j++) {
			rowValue += vector.getValue(j) * matrix.getValue(i, j);
		}
		result.setValue(i, rowValue);
	}
	return result;
}

// NEURAL NETWORK CLASSES

class NeuralNet {
	private:
		int inputs, hidden, outputs;
		Matrix hiddenWeights, outputWeights;
	public:
		NeuralNet(int, int, int);
		Vector evaluate(Vector);
};

NeuralNet::NeuralNet(int in, int hid, int out) {
	inputs = in;
	hidden = hid;
	outputs = out;

	hiddenWeights = Matrix(hidden, inputs, 0.5);
}

int main() {
	Matrix matrix(2, 3);
	Vector vector(3);

	matrix.setValue(0, 0, 1);
	matrix.setValue(0, 1, 3);
	matrix.setValue(0, 2, -2);

	matrix.setValue(1, 0, 2);
	matrix.setValue(1, 1, 5);
	matrix.setValue(1, 2, 4);

	vector.setValue(0, -1);
	vector.setValue(1, 5);
	vector.setValue(2, 2);

	cout << matrix.toString() << endl << endl;
	cout << vector.toString() << endl << endl;
	cout << (matrix * vector).toString() << endl;

	cin.get();
	return 0;
}