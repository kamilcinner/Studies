//Kamil Cinner IIST 3.2
#include <iostream>

using namespace std;

int licz(unsigned int x) {
	int w;
	if (x == 1) return 1;
	else {
		w = licz(x / 2);
		if (x % 2 == 1) return w + 1;
		else return w - 1;
	}
}

int main() {
	for (int i = 101; i < 200; i++) {
		if (licz(i) == 0) {
			cout << "0 dla " << i << endl;
			break;
		}
	}
	cout << licz(11) << endl;
	cout << licz(13) << endl;
	cout << licz(21) << endl;
	cout << licz(32) << endl;
	system("pause");
	return 0;
}