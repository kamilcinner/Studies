#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

int main()
{
	string s = "ABBAACCCAAABCCXYZCBBBAA";
	vector<char> znaki;
	bool istnieje;
	for (unsigned int i = 0; i < s.length(); i++) {
		istnieje = false;
		for (unsigned int j = 0; j < znaki.size(); j++)
			if (s[i] == znaki[j]) {
				istnieje = true;
				break;
			}
		if (!istnieje)
			znaki.push_back(s[i]);
	}
	cout << znaki.size();

	system("pause");
	return 0;
}