#include <iostream>
#include <vector>

using namespace std;


void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }
}

vector<double> Calc(vector<vector<double>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size() - 1; 

    for (int row = 0; row < numRows; row++) {

        int maxRow = row;
        for (int i = row + 1; i < numRows; i++) {
            if (abs(matrix[i][row]) > abs(matrix[maxRow][row])) {
                maxRow = i;
            }
        }   
        if (maxRow != row) {
            swap(matrix[row], matrix[maxRow]);
        }

        double pivot = matrix[row][row];
        for (int j = row; j <= numCols; j++) {
            matrix[row][j] /= pivot;
        }
        
        for (int i = 0; i < numRows; i++) {
            if (i != row) {
                double factor = matrix[i][row];
                for (int j = row; j <= numCols; j++) {
                    matrix[i][j] -= factor * matrix[row][j];
                }
            }
        }
    }

    vector<double> solution(numRows);
    for (int row = 0; row < numRows; row++) {
        solution[row] = matrix[row][numCols];
    }

    printMatrix(matrix);

    return solution;
}


int main(int argc, char** argv) {
	vector<vector<double>> matrix = vector<vector<double>>();
	for (int i = 0; i < 3; i++) {
		matrix.push_back(vector<double>());
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i].push_back(stof(argv[i * 4 + j + 1]));
		}
	}

    printMatrix(matrix);
    cout << endl;
  
    vector<double> solution = Calc(matrix);

    for (int i = 0; i < 3; i++) {
        cout << "X" << i + 1 << " = " << solution[i] << endl;
    }

    return 0;
}
