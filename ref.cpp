#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// newMatrix 函式用來簡化在程式中創建一個矩陣的寫法
vector<vector<double>> newMatrix(int row, int col) {
    return vector<vector<double>>(row, vector<double>(col));
}

void printMatrix(vector<vector<double>> mtx) {
    int row = mtx.size();
    int col = mtx[0].size();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mtx[i][j] << ' ';
        }
        cout << endl;
    }
}

// clearZeroRows 函式用來將矩陣的所有零列移至最下方
void clearZeroRows(vector<vector<double>> &mtx) {
    int row = mtx.size();
    int col = mtx[0].size();
    vector<vector<double>> non_zero_rows = newMatrix(0, 0);
    vector<vector<double>> zero_rows = newMatrix(0, 0);

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

// rowReduct 函式用來做高斯消去法中列的相減
void rowReduct(vector<double> &row1, vector<double> row2, int pivot_col_idx) {
    int row_len = row1.size();
    double mtp = row1[pivot_col_idx] / row2[pivot_col_idx]; // mtp 是 multiple 的縮寫，代表要乘 row2 的倍數
    for (int i = 0; i < row_len; i++) { // 執行列的相減
        row1[i] -= row2[i] * mtp;
        if (isZero(row1[i])) { // 解決浮點數誤差
            row1[i] = 0;
        }
    }
}

// ref 函式使用高斯消去法將矩陣轉換成列階梯形矩陣
void ref(vector<vector<double>> &mtx) {
    clearZeroRows(mtx); // 先將矩陣的所有零列移至最下方，避免多餘的操作與檢查

    // 向下執行高斯消去法
    int row = mtx.size();
    int col = mtx[0].size();
    int pivot_row_idx = 0; // pivot_row_idx 代表當前 pivot 的所在列數
    int pivot_col_idx = 0; // pivot_col_idx 代表當前 pivot 的所在行數
    while ((pivot_row_idx < row) && (pivot_col_idx < col)) { // 持續操作直到當前 pivot 超出矩陣範圍
        // 檢查當前 pivot 是否為0
        // 若當前 pivot 為0，則往下尋找當前 pivot 所在的行中第一個非零元素所在的列
        if (isZero(mtx[pivot_row_idx][pivot_col_idx])) {
            int next_non_zero_row_idx = pivot_row_idx + 1;
            while (next_non_zero_row_idx < row) {
                if (!isZero(mtx[next_non_zero_row_idx][pivot_col_idx])) { // 找到的話就交換這兩行，即可讓高斯消去繼續進行
                    swap(mtx[pivot_row_idx], mtx[next_non_zero_row_idx]);
                    break;
                }
                next_non_zero_row_idx++;
            }
            if (next_non_zero_row_idx >= row) { // 如果找不到，代表該行消去完成，接著尋找下一個 pivot
                pivot_col_idx++;
            }
        }

        // 若當前 pivot 不為0，則用該 pivot 列分別減去其下方所有的列
        else {
            for (int i = pivot_row_idx + 1; i < row; i++) {
                rowReduct(mtx[i], mtx[pivot_row_idx], pivot_col_idx);
            }
            pivot_row_idx++;
            pivot_col_idx++;
        }
    }

    clearZeroRows(mtx); // 高斯消去完成後，將過程中產生的零列都移至最下方
}

// rref 函式使用高斯消去法將矩陣轉換成簡化列階梯形矩陣
void rref(vector<vector<double>> &mtx) {
    // 先把矩陣轉換成列階梯形矩陣
    ref(mtx);

    // 將矩陣的每一行分別除以該行的pivot，使得每一行的pivot皆為1
    for (int i = 0; i < mtx.size(); i++) {
        for (int j = 0; j < mtx[i].size(); j++) {
            if (!isZero(mtx[i][j])) {
                double divisor = mtx[i][j];
                for (int k = j; k < mtx[i].size(); k++) {
                    mtx[i][k] /= divisor;
                }
                break;
            }
        }
    }

    // 向上執行高斯消去法，做法與向下的類似，目的是為了讓每一個pivot列只有pivot是1，其它元素都是0
    for (int i = 0; i < mtx.size(); i++) {
        for (int j = 0; j < mtx[i].size(); j++) {
            if (!isZero(mtx[i][j])) {
                for (int k = 0; k < i; k++) {
                    if (!isZero(mtx[k][j])) {
                        rowReduct(mtx[k], mtx[i], j);
                    }
                }
                break;
            }
        }
    }
}

int main() {
    int row, col;
    cout << "Please enter the number of rows of the matrix: ";
    cin >> row;
    cout << "Please enter the number of columns of the matrix: ";
    cin >> col;
    vector<vector<double>> mtx = newMatrix(row, col);
    cout << "Please enter the matrix: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> mtx[i][j];
        }
    }
    ref(mtx);
    cout << "The row echelon form of the matrix is: " << endl;
    printMatrix(mtx);
    rref(mtx);
    cout << "The reduced row echelon form of the matrix is: " << endl;
    printMatrix(mtx);
    return 0;
}
