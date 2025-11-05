#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void Create(int **a, const int k, const int n, const int Low, const int High, int i = 0, int j = 0) {
    if (i < k) {
        if (j < n) {
            a[i][j] = Low + rand() % (High - Low + 1);
            Create(a, k, n, Low, High, i, j + 1);
        } else {
            Create(a, k, n, Low, High, i + 1, 0);
        }
    }
}

void Print(int **a, const int k, const int n, int i = 0, int j = 0) {
    if (i < k) {
        if (j < n) {
            cout << setw(5) << a[i][j];
            Print(a, k, n, i, j + 1);
        } else {
            cout << endl;
            Print(a, k, n, i + 1, 0);
        }
    }
}

void FindMinMaxIndices(int row[], int n, int j, int& minIndex, int& maxIndex) {
    if (j == n) return;

    if (row[j] < row[minIndex])
        minIndex = j;
    if (row[j] > row[maxIndex])
        maxIndex = j;

    FindMinMaxIndices(row, n, j + 1, minIndex, maxIndex);
}

void SwapMinMaxInRows(int** matrix, int k, int n, int i = 0) {
    if (i == k) return;

    int minIndex = 0, maxIndex = 0;
    FindMinMaxIndices(matrix[i], n, 1, minIndex, maxIndex);

    int temp = matrix[i][minIndex];
    matrix[i][minIndex] = matrix[i][maxIndex];
    matrix[i][maxIndex] = temp;

    SwapMinMaxInRows(matrix, k, n, i + 1);
}

void SearchFirstEven(int **a, const int N, int i, int &kPos, int &minEven) {
    if (i >= N) return;

    int elem = a[i][N - 1 - i];

    if (elem % 2 == 0) {
        kPos = i;
        minEven = elem;
    } else {
        if (i < N - 1)
            SearchFirstEven(a, N, i + 1, kPos, minEven);
    }
}

void SearchMinEven(int **a, const int N, int i, int &minEven) {
    if (i >= N) return;

    int elem = a[i][N - 1 - i];
    if (elem % 2 == 0 && elem < minEven)
        minEven = elem;

    if (i < N - 1)
        SearchMinEven(a, N, i + 1, minEven);
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

    int kPos = -1;       
    int minEven = 0;     
    SearchFirstEven(Z, rows, 0, kPos, minEven);

    if (kPos == -1)
      cout<< "no 1 elem";
    else {
        SearchMinEven(Z, rows, kPos + 1, minEven);
        cout << "\n 1 elem on row = " << kPos << endl;
        cout << "min on diag = " << minEven << endl;
    }

    for (int i = 0; i < rows; i++)
        delete[] Z[i];
    delete[] Z;

    return 0;
}
