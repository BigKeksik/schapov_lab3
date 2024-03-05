#include <iostream>
#include "/opt/homebrew/Cellar/libomp/17.0.6/include/omp.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

double** createMatrix(int length, bool isSecond) {
    double** matrix = new double* [length];
    for (int i = 0; i < length; i++) {
        if (!isSecond) {
            matrix[i] = new double[length];
            for (int j = 0; j < length; j++) {
                matrix[i][j] = rand() % 10;
            }
        } else {
            matrix[i] = new double[1];
            matrix[i][0] = rand() % 10;
        }
    }
        
    return matrix;
}

void printMatrix(double** matrix, int length, bool isSecond) {
    for (int i = 0; i < length; i++) {
        if (!isSecond) {
            for(int j = 0; j < length; j++) {
                cout << matrix[i][j] << ' ';
            }
        } else {
            cout << matrix[i][0];
        }
        
        cout << endl;
    }
}

double* solveSystem(double** first, double** second, int length) {
    double* x = new double[length];

    #pragma omp parallel for
    for (int i = 0; i < length; ++i) {
        double div = first[i][i];
        #pragma omp parallel for
        for (int j = i; j < length; ++j) {
            first[i][j] /= div;
        }
        second[i][0] /= div;

        #pragma omp parallel for
        for (int k = i + 1; k < length; ++k) {
            double multiplier = first[k][i];
            for (int j = i; j < length; ++j) {
                first[k][j] -= multiplier * first[i][j];
            }
            second[k][0] -= multiplier * second[i][0];
        }
    }

    for (int i = length - 1; i >= 0; --i) {
        x[i] = second[i][0];
        #pragma omp parallel for
        for (int j = i + 1; j < length; ++j) {
            x[i] -= first[i][j] * x[j];
        }
    }

    return x;
}

int main() {
    double** a = createMatrix(3, false);
    double** b = createMatrix(3, true);
    printMatrix(a, 3, false);
    
    cout << endl << "x" << endl << endl;
    printMatrix(b, 3, true);
    cout << endl << "=" << endl << endl;
    double* result = solveSystem(a, b, 3);
    
    for(int i = 0; i < 3; i++) {
        cout << result[i] << endl;
    }

    return 0;
}
