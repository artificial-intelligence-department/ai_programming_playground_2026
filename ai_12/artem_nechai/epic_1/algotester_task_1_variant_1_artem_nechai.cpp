#include <iostream>

using namespace std;
int main()
{
	long long h, m, hi, mi;
	cin >> h >> m;
	for (int i = 0; i != 3; i++) {
		cin >> hi >> mi;
		if (hi != 0 && mi != 0) {
			cout << "NO" << endl;
			return 0;
		}
		else {
			h -= hi;
			m -= mi;
			if (h <= 0 || m <= 0) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	cout << "YES" << endl;
	return 0;
}
