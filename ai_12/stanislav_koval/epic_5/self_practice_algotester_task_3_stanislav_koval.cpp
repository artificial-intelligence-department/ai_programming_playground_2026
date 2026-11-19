\\Марічка вмикає лампи
#include <cstdio>

int main() {
    double m, n;

    scanf("%lf %lf", &m, &n);

    double answer = (m + 1) / (m + 1 - n);

    printf("%.9f\n", answer);
    
    return 0;
}