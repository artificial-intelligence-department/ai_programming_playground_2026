/*A plus B
Sofiia Chovhan AI 14
You are given two integers A and B. Your task is to calculate their sum.
Input
Two integers A and B separated by a single space.
Output
The sum of A and B.
Constraints
0 ≤𝐀 ≤100,
0 ≤𝐁 ≤100.
*/
#include <iostream>
int main() {
    int A, B;
    std:: cin >> A >> B;
    if(A >= 0 && A <= 100 && B >= 0 && B <= 100 ) {
        std :: cout << A + B;
    }
    return 0;
}
