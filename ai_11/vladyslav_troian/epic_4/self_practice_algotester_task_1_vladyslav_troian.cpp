#include <iostream>
using namespace std;

void sqrt(int n, int &k)
{
    int count = 1;
    int x = n;
    while (x > 2){
        x >>= 2;
        count *= 2;
    }
    double part;
    part = 1 + 0.5*(x-1) + 0.125*(x-1)*(x-1) + 0.0625*(x-1)*(x-1)*(x-1) + 0.0390625*(x-1)*(x-1)*(x-1)*(x-1);
    k = int(count * part);
}

void blocks_sum(int *req, int n, int k, int *block)
{
    for (int i = 0; i < n; i++){
        block[i/k] += req[i];
    }
}

void sum(int *req, int n, int m, int k, int *block)
{
    long long result = 0;
    int l = 0;
    int r = 0;
    int i = 0;
    int d = 0;
    for (int q = 0; q < m; q++){
        int a; 
        int b;
        int index;
        cin >> index >> a >> b;
        if (index == 1){
            l = a-1;
            r = b-1;
            while (l <= r){
                if (l % k == 0 && l + k - 1 <= r){
                    result += block[l/k];
                    l += k;
                } else {
                    result += req[l];
                    l++;
                }
            }
            cout << result << endl;
            result = 0;
        } else if (index == 2){
            i = a;
            d = b;
            req[i-1] += d;
            block[(i-1)/k] += d;
        }
    }
}

int main()
{
    int n = 0;
    int m = 0;
    cin >> n >> m;
    int *req = new int[n]();
    for (int k = 0; k < n; k++){
        cin >> req[k];
    }
    int k = 1;
    sqrt(n, k);
    int length = ((n-1+k)/k);
    int *block = new int[length];
    blocks_sum(req, n, k, block);
    sum(req, n, m, k, block);
    delete[] req;
    delete[] block;
    return 0;
}