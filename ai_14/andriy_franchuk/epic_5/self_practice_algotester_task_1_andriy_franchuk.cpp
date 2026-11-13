#include <stdio.h>

using namespace std;

double find_an(double n, double a1, double a2);

int main() {
    double n, a1, a2;
    scanf("%lf", &n);
    scanf("%lf", &a1);
    scanf("%lf", &a2);
    if(a1 > 0 && a2 > 0){
        printf("%c", '+');
        return 0;
    }else if(a1 < 0 && a2 < 0){
        printf("%c", '-');
        return 0;
    }else if(a1 == 0 && a2 == 0){
        printf("%c", '0');
        return 0;
    }

    double result = find_an(n, a1, a2);
    if(result > 0){
        printf("%c", '+');
    } else if(result == 0){
        printf("%c", '0');
    }else{
        printf("%c", '-');
    }
}

double find_an(double n, double a1, double a2){
    while(true){
        if(a1 > 0 && a2 > 0){
            return a2;
        }else if(a1 < 0 && a2 < 0){
            return a1;
        }else if(a1 == 0 && a2 == 0){
            return 0;
        }
        if(n == 0){
            return a1;
        }else if(n == 1){
            return a2;
        }else{
            double t = a1;
            a1 = a2;
            a2 = a2 + t;
            n--;
        }
    }
}