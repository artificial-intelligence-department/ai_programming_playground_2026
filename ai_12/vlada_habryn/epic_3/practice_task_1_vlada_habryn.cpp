
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_DAYS = 31;

void showSpending(double spending[], int days);
void showStats(double spending[], int days, double budget);
void checkLimit(double spending[], int days, double limit = 1000);
void showTop3(double spending[], int days);
void findMinMax(double spending[], int days, double& min, double& max);
double sumSpending(double spending[], int days);


int main() {
    cout << fixed << setprecision(2);
    double budget;
    int days;
    double spending[MAX_DAYS];
    
    cout << "Enter monthly budget: ";
    cin >> budget;
    while (cin.fail()||budget <=0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout<<" Invalid budget. Try again:";
        cin >> budget;
    }
    cout << "Enter number of days: ";
    cin >> days;
    while (cin.fail()||days <=0 || days > MAX_DAYS) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout<<" Invalid number of days. Try again:";
        cin >> days;
    }
for (int i = 0; i < days; i++) {
        cout << "Enter spending for day " << (i + 1) << ": ";
        cin >> spending[i];
        while (cin.fail()||spending[i] < 0) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout<<" Invalid spending. Try again:";
            cin >> spending[i];
        }
    }
    int choice;
    do {
    menu:
        cout << " Menu:" << endl;
        cout<< " 1. Show spending" << endl;
        cout << " 2. Statistics" << endl;
        cout<< "3. Days over daily limit" << endl;
        cout << "4. Top 3 spending days" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()||choice < 0 || choice > 4) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout<<" Invalid choice. Try again:";
            goto menu;
        }
        switch (choice) {
            case 1:
        showSpending(spending, days);
        break;

    case 2:
        showStats(spending, days, budget);
        break;

    case 3:
        checkLimit(spending, days);
        break;

    case 4:
        showTop3(spending, days);
        break;

    case 0:
        break;

        }
     } while (choice != 0);
    
return 0;
}
void showSpending(double spending[], int days) {
    cout << "Day Spending:" << endl;
    for (int i = 0; i < days; i++) {
        cout << i + 1 << "\t" << spending[i] << endl;
    }
} 
void checkLimit(double spending[], int days, double limit) {
    double input;
    cout << "Daily limit (0 = default):";
    cin >> input;
    while (cin.fail() || input < 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Invalid limit. Try again:";
        cin >> input;
    }
    if (input != 0) {
    limit = input;
    }
    cout << "Limit: " << limit << endl;
    int count = 0;
    for (int i = 0; i < days; i++) {
        if (spending[i] > limit) {
            cout << "Day " << i + 1 << ": " << spending[i] << endl;
            count++;
        }
    }
    cout << "Number of days over limit: " << count << endl;
}
void showTop3(double spending[], int days) {
    double sorted[MAX_DAYS];
    for (int i = 0; i < days; i++) {
        sorted[i] = spending[i];
    }
    for (int i = 0; i < days - 1; i++) {
        for (int j = 0; j < days - i - 1; j++) {
            if (sorted[j] < sorted[j + 1]) {
                double temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    cout << "Top 3 spending days:" << endl;
    for (int i = 0; i < 3 && i < days; i++) {
        cout << sorted[i] << endl;
    }
}

void findMinMax(double spending[], int days, double& min, double& max) {
    min = spending[0];
    max = spending[0];
    for (int i = 1; i < days; i++) {
        if (spending[i] < min) {
            min = spending[i];
        }
        if (spending[i] > max) {
            max = spending[i];
        }
    }

}
void showStats(double spending[], int days, double budget) {
    double min, max;
    double total;
    findMinMax(spending, days, min, max);
    total = sumSpending(spending, days);
    double remaining = budget - total;
    cout << "Statistics:" << endl;
    cout << "Minimum spending: " << min << endl;
    cout << "Maximum spending: " << max << endl;
    cout << "Total spending: " << total << endl;
    if (remaining < 0) {
        cout<< "Overspending: "<< fabs(remaining) << endl;
    } else {
        cout<< "Remaining budget: "<< remaining << endl;
    }
    int count = 0;
    for (int i = 0; i < days; i++) {
        if (spending[i] == 0) {
            continue;
        }
        count++;
    }
    cout << "Days with purchases: " << count << endl;
    double average = 0;
    if (count > 0) {
        average = total / count;
    }
    cout << "Average spending per day: " << average << endl;
    double spent = 0;
int i = 0;

while (i < days) {
    spent += spending[i];

    if (spent > budget) {
        break;
    }

    i++;
}

if (i < days) {
    cout << "Budget exceeded on day: " << i + 1
         << ", total spent: " << spent << endl;
}
}
double sumSpending(double spending[], int days) {
    if (days == 0){
        return 0;
    }
     return spending[days - 1] + sumSpending(spending, days - 1);
}