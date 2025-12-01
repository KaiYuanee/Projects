#include <iostream>
#include <vector>

using namespace std;

int main() {
    int row, col, add;
    cout << "Please enter the number of rows of the matrices: ";
    cin >> row;
    cout << "Please enter the number of columns of the matrices: ";
    cin >> col;
    vector<vector<double>> mtx(row, vector<double>(col));
    cout << "Please enter the first matrix:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> mtx[i][j];
        }
    }
    cout << "Please enter the second matrix:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> add;
            mtx[i][j] += add;
        }
    }
    cout << "The sum of the matrices is: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mtx[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
