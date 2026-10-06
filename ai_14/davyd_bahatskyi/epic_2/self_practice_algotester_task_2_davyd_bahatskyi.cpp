/*
 * Algotester: 0031 Kolya, Vasya and Tennis (Self Practice)
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */
#include <iostream>
#include <string>

using namespace std;

int main() {
  int n;
  if (!(cin >> n))
    return 0;
  string s;
  cin >> s;
  int k_games = 0, v_games = 0;
  int k_pts = 0, v_pts = 0;
  for (char c : s) {
    if (c == 'K') {
      k_pts++;
    } else if (c == 'V') {
      v_pts++;
    }
    if (k_pts >= 11 && (k_pts - v_pts) >= 2) {
      k_games++;
      k_pts = 0;
      v_pts = 0;
    } else if (v_pts >= 11 && (v_pts - k_pts) >= 2) {
      v_games++;
      k_pts = 0;
      v_pts = 0;
    }
  }
  cout << k_games << ":" << v_games << "\n";
  if (k_pts > 0 || v_pts > 0) {
    cout << k_pts << ":" << v_pts << "\n";
  }

  return 0;
}
