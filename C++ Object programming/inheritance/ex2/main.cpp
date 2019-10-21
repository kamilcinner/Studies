//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>

using namespace std;

class Animal {
	string name;
public:
	void setName(string name) {
		this->name = name;
	}
	const string& onChain() const {
		return name;
	}
	Animal(string name) {
		this->name = name;
	}
};

class Dog : public Animal {
public:
	void bark() {
		cout << "Hau! Hau!" << endl;
	}
	void giveMeAPaw() {
		cout << "Masz lape! (:)>>" << endl;
	}
	Dog(string name) : Animal(name) {}
};

int main() {
	Dog Basta("Basta");
	cout << "Imie: " << Basta.onChain() << endl;
	Basta.bark();
	Basta.giveMeAPaw();

	system("pause");
	return 0;
}