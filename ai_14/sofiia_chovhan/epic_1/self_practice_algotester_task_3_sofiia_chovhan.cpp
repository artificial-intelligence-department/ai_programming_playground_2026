/*Oranges
Sofiia Chovhan AI 14

Children measure themselves by various things. In our problem — by oranges. Marichka and Sofiyka are measuring themselves against Petryk.
It is necessary to determine whether Marichka and Sofiyka together have more oranges than Petryk.
Input
The first and only line contains three integers 𝑎, 𝑏, and 𝑐 — the number of oranges Marichka, Sofiyka, and Petryk have, respectively.
Output
In the single line, print the answer to the problem — YES if the girls together have more oranges than Petryk, or NO otherwise.
Constraints
1 ≤𝑎,𝑏,𝑐 ≤109.
*/
#include <iostream> 
int main() {
    int a, b, c;
    std :: cin >> a >> b >> c;
    if(a >= 1 && b >= 1 && c >=1 && a + b > c){
        std :: cout << "YES";
    }
    else {
        std :: cout << "NO";
    }
    return 0;
}