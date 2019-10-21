//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>

using namespace std;

class Animal {
	string name;
protected:
	int hunger;
	int thirst;
	int tiredness;
	int humor;
public:
	void setName(string name) {
		this->name = name;
	}
	virtual string getAnimalType() const {
		return "Zwierzatko: ";
	}
	ostream& onChain(ostream& stream) {
		stream << getAnimalType() << name << endl;
		stream << "Glod: " << hunger << endl;
		stream << "Pragnienie: " << thirst << endl;
		stream << "Zmeczenie: " << tiredness << endl;
		stream << "Humor: " << humor << endl;
		return stream;
	}
	Animal(string name = "Noname") {
		hunger = 0;
		thirst = 0;
		tiredness = 0;
		humor = 0;
		this->name = name;
	}
};

class lifeFunctions {
public:
	virtual void eat(int foodAmount) = 0;
	virtual void drink(int fluidAmount) = 0;
	virtual void sleep(int timeAmount) = 0;
	virtual void play(int timeAmount) = 0;
};

class Dog : public Animal, public lifeFunctions {
public:
	void bark() {
		cout << "Hau! Hau!" << endl;
	}
	void giveMeAPaw() {
		cout << "Masz lape! (:)>>" << endl;
	}
	void eat(int foodAmount) {
		hunger -= foodAmount;
	}
	void drink(int fluidAmount) {
		thirst -= fluidAmount;
	}
	void sleep(int timeAmount) {
		tiredness -= timeAmount;
	}
	void play(int timeAmount) {
		hunger += timeAmount;
		thirst += timeAmount;
		tiredness += timeAmount;
		humor += timeAmount;
	}
	string getAnimalType() const {
		return "Pies: ";
	}
	Dog(string name) : Animal(name) {}
};

class Cat : public Animal, public lifeFunctions {
public:
	void eat(int foodAmount) {
		hunger -= foodAmount;
	}
	void drink(int fluidAmount) {
		thirst -= fluidAmount;
	}
	void sleep(int timeAmount) {
		tiredness -= timeAmount;
	}
	void play(int timeAmount) {
		hunger += timeAmount;
		thirst += timeAmount;
		tiredness += timeAmount;
		humor += timeAmount;
	}
	void meow() {
		cout << "Meow <3" << endl;
	}
	void wash() {
		cout << "Meow meow - myju myju myju! <3" << endl;
	}
	string getAnimalType() const {
		return "Kot: ";
	}
	Cat(string name) : Animal(name) {}
};

class AnimalShelter {
	Animal* Animals;
public:
	int index;
	void addAnimal(Animal& A) {
		Animals[index] = A;
		index++;
	}
	Animal* getAnimal(int index) {
		return &Animals[index];
	}
	AnimalShelter() {
		index = 0;
		Animals = new Animal[100];
	}
	~AnimalShelter() {
		delete[] Animals;
	}
};

int main() {
	Dog Basta("Basta");
	Basta.play(5);
	Basta.onChain(cout) << endl;
	Basta.eat(4);
	Basta.onChain(cout) << endl;
	Basta.drink(3);
	Basta.onChain(cout) << endl;
	Basta.sleep(2);
	Basta.onChain(cout) << endl;

	Cat Mruczek("Mruczek");
	lifeFunctions& lfMruczek = Mruczek;
	lfMruczek.play(2);
	lfMruczek.eat(3);
	lfMruczek.drink(4);
	lfMruczek.sleep(5);
	dynamic_cast<Cat&>(lfMruczek).onChain(cout) << endl;

	Dog Rufus("Rufus");
	lifeFunctions& lfRufus = Rufus;
	lfRufus.play(10);
	lfRufus.eat(9);
	lfRufus.drink(8);
	lfRufus.sleep(7);
	dynamic_cast<Dog&>(lfRufus).onChain(cout) << endl;

	//lifeFunctions lF; - HeHe :))))

	system("pause");
	return 0;
}