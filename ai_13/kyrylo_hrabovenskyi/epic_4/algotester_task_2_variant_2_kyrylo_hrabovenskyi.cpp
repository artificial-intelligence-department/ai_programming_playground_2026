#include <iostream>
using namespace std;

int main()
{
    const int limit = 100000;
    int r[limit];
    int N;
    if (!(cin >> N)) return 0;
    for (int i = 0;i < N;i++)
    {
        if (!(cin >> r[i])) return 0;
    }
    int a, b, c;
    if (!(cin >> a >> b >> c)) return 0;

    int k[limit];
    int M = 0;
    int count_a = 1;
    int count_b = 1;
    int count_c = 1;
    for (int i = 0; i < N; i++)
    {
        if (r[i] == a && count_a > 0) {
            count_a--;
        }
        else if (r[i] == b && count_b > 0) {
            count_b--;
        }
        else if (r[i] == c && count_c > 0) {
            count_c--;
        }
        else {
            k[M] = r[i];
            M++;
        }
    }
    if (M <= 1) {
        cout << 0 << "\n\n";
        return 0;
    }
    int count_sums = M - 1;
    cout << count_sums << "\n";

    for (int i = 0; i < count_sums; i++)
    {
        int current_sum = k[i] + k[i + 1];
        cout << current_sum << (i == count_sums - 1 ? "" : " ");
    }

    return 0;

}
