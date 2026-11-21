// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40498

#include <cstdio>

using namespace std;

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (a + 1 < b) {
        printf("%d\n", a + 1);
    } else {
        printf("-1\n");
    }
    return 0;
}
