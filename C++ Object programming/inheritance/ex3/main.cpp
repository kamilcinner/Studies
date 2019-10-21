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
	string getAnimalType() const {
		return "Zwierzatko: ";
	}
	string onChain() const {
		return getAnimalType() + name;
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
	string getAnimalType() const {
		return "Pies: ";
	}
	Dog(string name) : Animal(name) {}
};

int main() {
	Dog Basta("Basta");
	cout << Basta.onChain() << endl;

	Basta.getAnimalType();
	cout << endl;
	
	Basta.bark();
	Basta.giveMeAPaw();

	system("pause");
	return 0;
}