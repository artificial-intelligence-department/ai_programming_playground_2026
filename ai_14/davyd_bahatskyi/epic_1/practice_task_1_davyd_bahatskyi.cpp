/*
 * Автономність портативної зарядної станції
 * davyd_bahatskyi
 * ai_14
 */
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main() {
  // user input
  string name;
  cout << "charging station model name: ";
  cin >> name;
  if (name.length() > 31) { // if the name is longer than 31 characters
    cout << "error: name length must be no more than 31 characters.\n";
    return 1;
  }

  double C;
  cout << "advertised capacity (Wh): ";
  cin >> C;
  if (C <= 0) { // if capacity is negative
    cout << "error: advertised capacity must be more than 0.\n";
    return 1;
  }

  int years;
  cout << "station age (years): ";
  cin >> years;
  if (years < 0 || years > 20) { // if age isnt between 0 and 20
    cout << "error: station age should be from 0 to 20.\n";
    return 1;
  }

  int charge;
  cout << "charge (%): ";
  cin >> charge;
  if (charge < 0 || charge > 100) { // if charge is outside 0 to 100 range
    cout << "error: charge must be from 0 to 100.\n";
    return 1;
  }

  double eff;
  cout << "efficiency (%): ";
  cin >> eff;
  if (eff <= 0 || eff > 100) { // if efficiency is outside 0 to 100 range
    cout << "error: efficiency must be more than 0 and no more than 100.\n";
    return 1;
  }

  double P;
  cout << "power output (W): ";
  cin >> P;
  if (P <= 0) { // if power output is negative
    cout << "error: power output should be more than 0.\n";
    return 1;
  }
  // end of user input

  // introducing variables
  double C_eff, E_stored, E_useful, E_loss, T;
  int h, m;

  // degration rate of the batery
  const double deg_rate = 2;
  // calculating capacity accounting for its age
  C_eff = C * pow((1.0 - deg_rate / 100.0), years);
  E_stored = C_eff * charge / 100.0;
  E_useful = E_stored * eff / 100.0;
  E_loss = E_stored - E_useful;
  // time that the charging station can work for at its power output
  T = E_useful / P;
  // time in hours and minutes
  h = (int)T;
  m = (int)((T - h) * 60.0);

  // final output
  cout << "\nstation name: " << name << "\n";
  cout << "advertised capacity: " << trunc(10.0 * C) / 10.0 << " Wh\n";
  cout << "station age: " << years << " years\n";
  cout << "actual capacity accounting for age: " << trunc(10.0 * C_eff) / 10.0
       << " Wh\n";
  cout << "charge: " << charge << " %\n";
  cout << "efficiency: " << eff << " %\n";
  cout << "stored energy: " << trunc(10.0 * E_stored) / 10.0 << " Wh\n";
  cout << "useful energy: " << trunc(10.0 * E_useful) / 10.0 << " Wh\n";
  cout << "lost energy: " << trunc(10.0 * E_loss) / 10.0 << " Wh\n";
  cout << "time left: " << trunc(100.0 * T) / 100.0 << " h  = " << h << " h "
       << (m < 10 ? "0" : "") << m << " m\n";

  return 0;
}
