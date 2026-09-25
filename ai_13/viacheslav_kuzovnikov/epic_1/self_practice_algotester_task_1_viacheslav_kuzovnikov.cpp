/*
3+1
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

# include <iostream>
using namespace std;
int main (){
    int a;
    int b;
    int c; 
    int d;
  
    cin >> a;
    if (a < 100 || a > 1000){
    
        return 1;
    }


    cin >> b;
    if (b < 100 || b > 1000){
      
        return 1;
    }

    
    cin >> c;
    if (c < 100 || c > 1000){
       
        return 1;
    }

    cin >> d;
    if (d < 100 || d > 1000){
       
        return 1;
    }

    int m [4] = {a, b, c, d};
    int min = m[0];
    for (int i = 1; i < 4; i++) {
        if (m[i] < min) {
            min = m[i]; 
        }
    }

    int sum = a + b + c + d - min;
    cout  << sum << endl;


    return 0;
}