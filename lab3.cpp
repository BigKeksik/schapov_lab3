#include <iostream>

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

int main() {
    int length = 3;
    double** matrix = createMatrix(length, false);
    
    printMatrix(matrix, length, false);
    
    return 0;
}
