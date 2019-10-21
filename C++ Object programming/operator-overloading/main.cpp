//Kamil Cinner IIST 3.2
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <assert.h>

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
	const string& getName() const {
		return name;
	}
	virtual const string getAnimalType() {
		return "Zwierzatko: ";
	}
	virtual string getAnimalGender() = 0;
	ostream& onChain(ostream& stream) {
		stream << getAnimalType() << name << "  ";
		stream << getAnimalGender() << endl;
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
	enum Genders { Pies, Suka };
	Genders gender;
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
	const string getAnimalType() {
		return "Pies: ";
	}
	virtual string getAnimalGender() {
		string temp;
		switch (gender) {
			case 0: temp = "Pies"; break;
			case 1: temp = "Suka";
		}
		return "Plec: " + temp;
	}
	Dog operator + (Dog& D) {
		assert(gender != D.gender);
		Dog newDog(this->getName() + " aka " + D.getName(), rand() % 2);
		return newDog;
	}
	Dog(string name, int gen) : Animal(name) {
		gender = static_cast<Genders>(gen);
	}
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
	const string getAnimalType() {
		return "Kot: ";
	}
	Cat(string name) : Animal(name) {}
};

//class AnimalShelter {
//	Animal* Animals;
//	int AnimalsIndex;
//public:
//	void addAnimal(Animal& A) {
//		Animals[AnimalsIndex] = A;
//		AnimalsIndex++;
//	}
//	Animal* getAnimal(int index) {
//		return &Animals[index];
//	}
//	AnimalShelter() {
//		AnimalsIndex = 0;
//		Animals = new Animal[100];
//	}
//	~AnimalShelter() {
//		delete[] Animals;
//	}
//};

int main() {
	srand(time(NULL));

	Dog Basta("Basta", 1);
	Dog Rufus("Rufus", 0);

	Dog Nowy = Basta + Rufus;
	Nowy.onChain(cout) << endl;

	system("pause");
	return 0;
}