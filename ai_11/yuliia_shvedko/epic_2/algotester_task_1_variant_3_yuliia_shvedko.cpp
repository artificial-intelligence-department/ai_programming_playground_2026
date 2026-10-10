/*Лабораторна робота №1, алготестер варіант 3
Група: ШІ-11
Автор: Шведько Юлія*/

#include <iostream>
using namespace std;

int main()
{
    long long a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    if (a <= 0 ){
        cout << "ERROR" << endl;
        return 0;}
    if (b <= 0 ){
        cout << "ERROR" << endl;
        return 0;}
    else if (b > a){
        cout << "LOSS" << endl;
        return 0;}
    if (c <= 0 ){
        cout << "ERROR" << endl;
        return 0;}
    else if (c > b){
        cout << "LOSS" << endl;
        return 0;}
    if (d <= 0 ){
        cout << "ERROR" << endl;
        return 0;}
    else if (d > c){
        cout << "LOSS" << endl;
        return 0;}
    if (e <= 0 ){
        cout << "ERROR" << endl;
        return 0;}
    else if (e > d){
        cout << "LOSS" << endl;
        return 0;}

    cout << "WIN" << endl;

    return 0;
}