#include <iostream>

using namespace std;
int main()
{
	long long n;
	cin >> n; 
	if (n <= 0) {
		cout << "ERROR";
		return 0;
	}
	long long n0 = n;
	for (int i = 1; i != 5; i++) {
		cin >> n;
		if (n > n0) {
			cout << "LOSS";
			return 0;
		}
		else if (n <= 0) {
			cout << "ERROR";
			return 0;
		}
		n0 = n;
	}
	cout << "WIN";
	return 0;
}
