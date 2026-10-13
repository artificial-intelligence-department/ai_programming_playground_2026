/* 
Задача: Algotester Self-Practice №2.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
int n = 0;
cin >> n;
int a[100005] = {0};
int parni = 0;
int neparni = 0;
for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i]  % 2 == 0) parni++;
    else neparni++;
}
if (parni - neparni > 1 || neparni - parni > 1) {
cout << "-1"; 
return 0;}

if (parni > neparni) {
for  (int i = 0; i < n; i++) {
   if (i % 2 == 0 && a[i] % 2 != 0) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] % 2 == 0) {
                int k = a[i];
                a[i] = a[j];
                a[j] = k;
                break;}}}
    
    
    
   if (i % 2 != 0 && a[i] % 2 == 0) {
        for (int j = i + 1; j < n; j++) {
        if (a[j] % 2 != 0) {
        int k = a[i];
        a[i] = a[j];
        a[j] = k; break; }}}}}

else {
for (int i = 0; i < n; i++) {
    if (i % 2 == 0 && a[i] % 2 == 0) {
    for (int j = i + 1; j < n; j++) {
    if (a[j] % 2 != 0) { 
    int k = a[i];
    a[i] = a[j];
    a[j] = k; break;}}}
         
    if (i % 2 != 0 && a[i] % 2 != 0) {
    for (int j = i + 1; j < n; j++) {
    if (a[j] % 2 == 0) { 
    int k = a[i];
    a[i] = a[j];
    a[j] = k; break;}}}}}

for (int i = 0; i < n; i++) cout << a[i] << " ";
return 0;
}