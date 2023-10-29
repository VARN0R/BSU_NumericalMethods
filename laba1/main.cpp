#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;


void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << setw(20) << value;
        }
        cout << endl;
    }
}

vector<double> solveLinearSystem(vector<vector<double>> matrix, vector<double> keys) {
    
    for (int i = 0; i < keys.size(); i++){
        matrix[i].push_back(keys[i]); 
    }

    cout << "Merge keys and matrix" <<  endl;
    printMatrix(matrix);
    cout << endl;    

    int numRows = matrix.size();
    int numCols = matrix[0].size() - 1; 

    // find the main element
    for (int row = 0; row < numRows; row++) {
        int maxRow = row;
        for (int i = row + 1; i < numRows; i++) {
            if (abs(matrix[i][row]) > abs(matrix[maxRow][row])) {
                maxRow = i;
            }
        }
        // If necessary, moved the strings    
        if (maxRow != row) {
            swap(matrix[row], matrix[maxRow]);
        }
        
        //[0][0] [0][1] [0][2] [0][3] [0][4]
        //[1][0] [1][1] [1][2] [1][3] [1][4]
        //[2][0] [2][1] [2][2] [2][3] [2][4]
        //[3][0] [3][1] [3][2] [3][3] [3][4]
        //[4][0] [4][1] [4][2] [4][3] [4][4]

        // Divide into the main element, 1 should appear 
        double pivot = matrix[row][row];
        if(pivot == 0){
            cout << "pivot can not be 0";
        }
        for (int j = row; j <= numCols; j++) {
            matrix[row][j] /= pivot;
        }

        // making zeros in columns        
        for (int i = 0; i < numRows; i++) {
            if (i != row) {
                double factor = matrix[i][row];
                for (int j = row; j <= numCols; j++) {
                    matrix[i][j] -= factor * matrix[row][j];
                }
            }
        }
        cout << "Already making zeros in columns" << endl;
        printMatrix(matrix);
        cout << endl;
    }

    // Receiving the vector of x`s 
    vector<double> solution(numRows);
    for (int row = 0; row < numRows; row++) {
        solution[row] = matrix[row][numCols];
    }

    cout << "Result: " << endl;
    printMatrix(matrix);
    cout << endl;

    return solution;
}

vector<double> findVectorNev(vector<vector<double>> matrix, vector<double> keys, vector<double> solution){
    vector<double>nev;
    double ans = 0;
    int countSolution = 0;
    int countKeys = 0;
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            ans+=(value*solution[countSolution]);
            cout << value << "*" << solution[countSolution] << endl;
            countSolution++;
        }
        nev.push_back(ans - keys[countKeys]);
        countKeys++;
        countSolution = 0;
        ans = 0;
    }
    cout << endl;
    return nev; 
}


double calcRelativeError(vector<double> solutionsVector, vector<double> solutionsVectorDouble){
   double q = 0.0;
   double maxSolutionsVector = *max_element(solutionsVector.begin(), solutionsVector.end());
   for(int i=0;i<solutionsVector.size();i++){
       q = max(q, abs(solutionsVectorDouble[i] - solutionsVector[i]));
   }
   return q / maxSolutionsVector;
}



int main(int argc, char** argv) {
	vector<vector<double>> matrix{};
	vector<double>keys;
    int colLen = 3;
    int rowLen = 4;
    
    for (int i = 0; i < colLen; i++) {
		matrix.push_back(vector<double>());
	}
	for (int i = 0; i < colLen; i++) {
		for (int j = 0; j < 4; j++) {
			if(j == 3){
                keys.push_back(stof(argv[i * 4 + j + 1]));
            } else {
                 matrix[i].push_back(stof(argv[i * 4 + j + 1]));
            }
           
		}
	}
    cout << "Input matrix: " << endl;
    printMatrix(matrix);
    cout << endl;

    for (int i = 0; i < keys.size(); i++){
        cout << keys[i] << endl;
    }

    vector<double> solutionsVector = solveLinearSystem(matrix, keys);
	cout << "Vector of solution system: " << endl;
	for (int i = 0; i < colLen; i++) {
		cout << "X" << i + 1 << " = " << solutionsVector[i] << endl;
	}
	cout << endl;

	vector<double> solutionsVectorDouble = solveLinearSystem(matrix, solutionsVector);
	cout << "Vector of double solution system: " << endl;
	for (int i = 0; i < colLen; i++) {
		cout << "X" << i + 1 << " = " << solutionsVectorDouble[i] << endl;
	}
	cout << endl;

	double q = calcRelativeError(solutionsVector, solutionsVectorDouble);
	cout << "Relative error: " << q << endl;
    cout << endl;

    vector<double> nev = findVectorNev(matrix, keys, solutionsVector);
    cout << "Vector of discrepancy(невязки): ";
    for (int i = 0; i < colLen; i++) {
        cout << nev[i] << " ";
    }
    cout << endl;
    return 0;

}
