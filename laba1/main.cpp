#include "funcs.h"

int main(int argc, char** argv) {
	vector<vector<double>> matrix{};
	vector<double>keys;
    int colLen = 3;
    int rowLen = 4;
    
    for (int i = 0; i < colLen; i++) {
		matrix.push_back(vector<double>());
	}
	for (int i = 0; i < colLen; i++) {
		for (int j = 0; j < rowLen; j++) {
			if(j == 3){
                keys.push_back(stof(argv[i * rowLen + j + 1]));
            } else {
                 matrix[i].push_back(stof(argv[i * rowLen + j + 1]));
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

    cout << "Standard of discrepancy(невязки): ";
    cout << max(nev[0], max(nev[1], nev[2])); 
    return 0;

}
