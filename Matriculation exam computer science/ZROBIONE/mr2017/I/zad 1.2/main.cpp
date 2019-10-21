//Kamil Cinner IIST 3.2
#include <iostream>
#include <vector>

using namespace std;

void solution(int A[], const int &n, const int &p) {
	int max1, max2;
	max1 = max2 = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] % p != 0) {
			if (A[i] > max1) {
				max2 = max1;
				max1 = A[i];
			}
			else if (A[i] > max2) {
				max2 = A[i];
			}
		}
	}
	cout << max1 * max2;
}

int main() {
	int A[] = { 1,5,9,23,33,6,4,75 };
	solution(A, 8, 3);
	cout << endl;
	system("pause");
	return 0;
}