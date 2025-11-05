#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void Create(int **a, const int k, const int n, const int Low, const int High) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

void Print(int **a, const int k, const int n) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
}

void FindMinMaxIndices(int row[], int n, int &minIndex, int &maxIndex) {
    minIndex = 0;
    maxIndex = 0;
    for (int j = 1; j < n; j++) {
        if (row[j] < row[minIndex])
            minIndex = j;
        if (row[j] > row[maxIndex])
            maxIndex = j;
    }
}

void SwapMinMaxInRows(int **matrix, int k, int n) {
    for (int i = 0; i < k; i++) {
        int minIndex, maxIndex;
        FindMinMaxIndices(matrix[i], n, minIndex, maxIndex);
        int temp = matrix[i][minIndex];
        matrix[i][minIndex] = matrix[i][maxIndex];
        matrix[i][maxIndex] = temp;
    }
}

bool SearchMinEven(int **a, const int N, int &k, int &minEven) {
    k = -1; 
    int j;

    for (int i = 0; i < N; i++) {
        j = N - 1 - i;  
        if (a[i][j] % 2 == 0) {
            k = i;
            minEven = a[i][j];
            break; }
    }

    if (k == -1)
        return false;

    for (int i = k + 1; i < N; i++) {
        j = N - 1 - i;
        if (a[i][j] % 2 == 0 && a[i][j] < minEven)
            minEven = a[i][j];
    }

    return true;
}

int main() {
    srand((unsigned)time(NULL));

    int rows, cols;
    cout << "row: ";
    cin >> rows;
    cout << "col: ";
    cin >> cols;

    const int Low = -5;
    const int High = 10;

    int **Z = new int*[rows];
    for (int i = 0; i < rows; i++)
        Z[i] = new int[cols];

    Create(Z, rows, cols, Low, High);
    cout << "\nstart:\n";
    Print(Z, rows, cols);

    SwapMinMaxInRows(Z, rows, cols);
    cout << "\nswap:\n";
    Print(Z, rows, cols);

    int k, minEven;
    if (SearchMinEven(Z, rows, k, minEven)) {
        cout << "\n 1 elem on row = " << k << endl;
        cout << "min on diag = " << minEven << endl;
    } else {
        cout << "\ndiag has not elem\n";
    }

    for (int i = 0; i < rows; i++)
        delete[] Z[i];
    delete[] Z;

    return 0;
}
