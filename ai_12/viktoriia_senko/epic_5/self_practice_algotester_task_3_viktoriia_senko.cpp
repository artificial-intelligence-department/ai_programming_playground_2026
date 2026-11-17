//Задача №0132 "Назва для покемона"
#include <cstdio>
#include <cstring>

int main() {
    char t[1001];
    char s[1001];

    if (scanf("%s %s", t, s) != 2) return 0;
    int n=strlen(t);
    int m=strlen(s);

    if (n<m) {
        printf("NO\n");
        return 0;
    }

    bool found=false;
    for (int i=0; i<=n-m; i++) {
        bool ok=true;
        for (int j=0; j<m; j++) {
            if (t[i + j] != '?' && t[i + j] != s[j]) {
                ok=false;
                break;
            }
        }
        if (ok) {
            found=true;
            break; 
        }
    }

    if (found) printf("YES\n");
    else printf("NO\n");

    return 0;
}