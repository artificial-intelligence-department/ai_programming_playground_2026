#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    if (scanf("%d", &n) != 1){
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
    }

    auto end0 = partition(a.begin(), a.end(), [](int x){
        return x % 3 == 0;
    });

    auto end1 = partition(end0, a.end(), [](int x){
        return x % 3 == 1;
    });

    sort(a.begin(), end0);
    sort(end0, end1);
    reverse(end0, end1);
    sort(end1, a.end());

    a.erase(unique(a.begin(), a.end()), a.end());

    printf("%zu\n", a.size());
    for (size_t i = 0; i < a.size(); ++i){
        if (i > 0){
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}