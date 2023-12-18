#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Matrix {
private:
	vector<vector<T>> data;
	int rows;
	int cols;
public:
	Matrix(int rows, int cols)
	: rows(rows), cols(cols)
	{
		data.resize(rows, vector<T>(cols, T()));
	}

	void setValue(int row, int col, T value) {
		if (row < 0 | row >= rows || col < 0 || col >= cols) {
			throw out_of_range("Dimensional error");
		}
		data[row][col] = value;
	}

	T getValue(int row, int col) const {
		if (row < 0 | row >= rows || col < 0 || col >= cols) {
			throw out_of_range("Dimensional error");
		}
		return data[row][col];
	}

	Matrix<T> operator+(const Matrix<T>& other) const {
		if (rows != other.rows || cols != other.cols) throw invalid_argument("Matrix dimension mismatch for addition");

		Matrix<T> result(rows, cols);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}

		return result;
	}

	Matrix<T> operator-(const Matrix<T>& other) const {
		if (rows != other.rows || cols != other.cols) throw invalid_argument("Matrix dimension mismatch for subtraction");

		Matrix<T> result(rows, cols);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result.data[i][j] = data[i][j] - other.data[i][j];
			}
		}

		return result;
	}

	Matrix<T> operator*(const Matrix<T>& other) const {
		if (cols != other.rows) throw invalid_argument("Matrix dimension mismatch for multiplication");

		Matrix<T> result(rows, other.cols);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < other.cols; j++) {
				result.data[i][j] = 0;
				for (int k = 0; k < cols; k++) {
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
	}
};

int main() {
	try {
		Matrix<int> mat1(2, 3);
		Matrix<int> mat2(3, 2);

		mat1.setValue(0, 0, 1);
		mat1.setValue(0, 1, 2);
		mat1.setValue(0, 2, 3);
		mat1.setValue(1, 0, 4);
		mat1.setValue(1, 1, 5);
		mat1.setValue(1, 2, 6);

		mat2.setValue(0, 0, 7);
		mat2.setValue(0, 1, 8);
		mat2.setValue(1, 0, 9);
		mat2.setValue(1, 1, 10);
		mat2.setValue(2, 0, 11);
		mat2.setValue(2, 1, 12);
        //Missing << overloading 
		Matrix<int> additionResult = mat1 + mat2;
		Matrix<int> subtractionResult = mat1 - mat2;
		Matrix<int> multiplicationResult = mat1 * mat2;

	}
	catch (const exception& e) {
		cout << "Caught an exception: " << e.what() << endl;
	}
}