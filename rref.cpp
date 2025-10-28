#include <iostream>
#include <vector>

using namespace std;

// clearZeroRows 函式用來將矩陣的所有零列移至最下方
void clearZeroRows(vector<vector<double>> &mtx) {
    int row = mtx.size();
    int col = mtx[0].size();
    vector<vector<double>> non_zero_rows;
    vector<vector<double>> zero_rows;

    // 遍歷整個矩陣，檢查各列是否為零列並存放在相應的陣列
    for (int i = 0; i < row; i++) {
        bool is_zero_row = true;
        for (int j = 0; j < col; j++) {
            if (mtx[i][j] != 0) {
                is_zero_row = false;
                break;
            }
        }
        if (is_zero_row) {
            zero_rows.push_back(mtx[i]);
        } else {
            non_zero_rows.push_back(mtx[i]);
        }
    }

    // 將矩陣清空後再依序加入非零列及零列
    mtx.clear();
    mtx.insert(mtx.end(), non_zero_rows.begin(), non_zero_rows.end());
    mtx.insert(mtx.end(), zero_rows.begin(), zero_rows.end());
}

// isZero 函式用來判斷一個極小的數是否可被視為0，在此用來解決高斯消去的浮點數誤差
bool isZero(double num) {
    double epsilon = 1e-10; // 容許誤差在10的-10次方以內
    return fabs(num) < epsilon;
}

int main() {
    int row, col;
    cin >> row >> col;
    vector<vector<double>> mtx(row, vector<double>(col));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> mtx[i][j];
        }
    }
    clearZeroRows(mtx);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mtx[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
