/* 
Задача: Лабораторна робота №4. Завдання 1. Варіант №2. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
int m[100];
int m2[100];
int m3[200];

srand(static_cast<unsigned int>(time(nullptr)));
int rozmir = 0;
cin >> rozmir;
if(rozmir < 0 || rozmir > 100) return 0;

for(int i = 0; i < rozmir; i++) {
    m[i] = rand() % 101;
    cout << m[i] << " ";}

int zero = 0;
for(int i = 0; i < rozmir; i++) {
if(m[i] == 0) {
    zero = 1;
    m[i] = -1; 
    break;}}
cout << endl;

int bez_zero = rozmir;
if(zero > 0) {
bez_zero = rozmir - 1;
int j = 0;
for(int i = 0; i < rozmir; i++) {
    if(m[i] == -1) continue;
    if(m[i] != -1) { m2[j] = m[i]; j++; }}} 

else {
for(int i = 0; i < rozmir; i++) {
m2[i] = m[i];}}

int count = 0;
for(int i = 0; i < bez_zero; i++) {
    if(m2[i] % 2 == 0 && m2[i] != 0) { count++; }}

int m3_rozmir = bez_zero + count;
int k = 0;
for(int i = 0; i < bez_zero; i++) {
    if(m2[i] % 2 == 1) { 
    m3[k] = m2[i]; 
    k++; }

else {
if(i == 0) { 
    m3[k] = m2[i]; 
    m3[k + 1] = 0 + 2; }

else { 
m3[k] = m2[i]; 
m3[k + 1] = m3[k - 1] + 2;}
k += 2;}}

for(int i = 0; i < m3_rozmir; i++) {
    cout << m3[i] << " ";}

    return 0;
}
