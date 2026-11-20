#include <iostream>
using namespace std;

void mergeSort(char *a, char *temp, int left, int right)
{
    if (left >= right) return;

    int mid = left + (right - left)/2;
    mergeSort(a, temp, left, mid);
    mergeSort(a, temp, mid+1, right);

    int i = left;
    int j = mid+1;
    int k = left;

    while (i <= mid && j <= right){
        if (a[i] <= a[j]){
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid){
        temp[k++] = a[i++];
    }
    while (j <= right){
        temp[k++] = a[j++];
    }
    for (int i = left; i <= right; i++){
        a[i] = temp[i];
    }
}

void unique(char *a, int &len, char *temp)
{
    for (int i = 0; i < len; i++){
        temp[i] = 0;
    }
    
    int k = 0;
    int newlen = len+1;
    for (int i = 0; i < len; i++){
        if (a[i-k] == a[i]){
            temp[i-k] = a[i-k];
            k++;
            newlen--;
        } else {
            temp[i] = a[i];
            k = 1;
        }
    }
    
    k = 0;
    for (int i = 0; i < len; i++){
        if (temp[i] == 0){
            k++;
        } else {
            a[i-k] = temp[i];
        }
    }

    len = newlen;
}

bool P(int x, int y, int i, int j)
{
    int P_rows[1] = {i+1};
    if (P_rows[0] == x){
        int P_cals[2] ={j-1, j+1};
        if (P_cals[0] == y){
            return true;
        } else if (P_cals[1] == y){
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool R(int rows, int cals, int x, int y, int start_i, int start_j)
{
    int i = (start_i+1) % rows;
    while (i != start_i){
        if (i == x && start_j == y){
            return true;
        }
        ++i %= rows;
    }
    int j = (start_j+1) % cals;
    while (j != start_j){
        if (j == y && start_i == x){
            return true;
        }
        ++j %= cals;
    }
    return false;
}

bool N(int x, int y, int i, int j)
{
    int N_rows[4] = {i+2, i-2, i+1, i-1};
    int N_cals[4] = {j+1, j-1, j+2, j-2};
    if (N_cals[2] == y && (N_rows[2] == x || N_rows[3] == x)){
        return true;
    } else if (N_cals[3] == y && (N_rows[2] == x || N_rows[3] == x)){
        return true;
    } else if (N_rows[0] == x && (N_cals[0] == y || N_cals[1] == y)){
        return true;
    } else if (N_rows[1] == x && (N_cals[0] == y || N_cals[1] == y)){
        return true;
    } else {
        return false;
    }
}

bool B(int x, int y, int start_i, int start_j)
{
    return abs(x - start_i) == abs(y - start_j);
}

bool K(int x, int y, int i, int j)
{
    int K_rows[3] = {i+1, i, i-1};
    for (int q = 0; q < 3; q++){
        if (K_rows[q] == x){
            int K_cals[3] = {j-1, j, j+1};
            for (int l = 0; l < 3; l++){
                if (K_cals[l] == y){
                    return true;
                }
            }
        }
    }
    return false;
}

void attack(char *result, char desk[8][8], int n, int x, int y)
{
    if (desk[x-1][y-1] != 'O'){
        cout << 'X' << endl;
        return;
    }

    int k = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (desk[i][j] == 'P' && P(x-1, y-1, i, j)){
                result[k] = 'P';
                k++;
            } else if (desk[i][j] == 'R' && R(n, n, x-1, y-1, i, j)){
                result[k] = 'R';
                k++;
            } else if (desk[i][j] == 'N' && N(x-1, y-1, i, j)){
                result[k] = 'N';
                k++;
            } else if (desk[i][j] == 'B' && B(x-1, y-1, i, j)){
                result[k] = 'B';
                k++;
            } else if (desk[i][j] == 'Q' && (B(x-1, y-1, i, j) || R(n, n, x-1, y-1, i, j))){
                result[k] = 'Q';
                k++;
            } else if (desk[i][j] == 'K' && K(x-1, y-1, i, j)){
                result[k] = 'K';
                k++;
            }
        }
    }

    if (k == 0){
        k++;
        result[0] = 'O';
    }
    char *temp = new char[k];
    mergeSort(result, temp, 0, k-1);
    unique(result, k, temp);
    delete[] temp;
    for (int i = 0; i < k; i++){
        cout << result[i];
    }
    cout << endl;
}

int main()
{
    const int n = 8;
    char desk[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> desk[i][j];
        }
    }
    int Q;
    cin >> Q;
    int x;
    int y;
    char result[65] = {0};
    for (int i = 0; i < Q; i++){
        cin >> x >> y;
        attack(result, desk, n, x, y);
    }
    return 0;
}