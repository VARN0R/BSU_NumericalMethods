#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

void printMatrix(const vector<vector<double>>& matrix);

vector<double> solveLinearSystem(vector<vector<double>> 
    matrix,const vector<double>& keys);

vector<double> findVectorNev(vector<vector<double>> matrix, 
    const vector<double>& keys,
    const vector<double>& solution);

double calcRelativeError(const vector<double>& solutionsVector,
    const vector<double>& solutionsVectorDouble);
 