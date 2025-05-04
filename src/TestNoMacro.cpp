#include <boost/openmethod.hpp>
#include <boost/openmethod/compiler.hpp>

#include <iostream>

struct Animal {
	Animal(std::string name) :
			name(name) {
	}
	std::string name;
	int actions = 0;
	virtual ~Animal() = default;
};

struct Cat: Animal {
	using Animal::Animal;
};

struct Dog: Animal {
	using Animal::Animal;
};

struct Bulldog: Dog {
	using Dog::Dog;
};

using namespace boost::openmethod;

static use_classes<Animal, Cat, Dog, Bulldog> animal_classes;

class play_openmethod;

using play = method<play_openmethod(virtual_ptr<Animal>), void>;

void play_animal(virtual_ptr<Animal> animal) {
	std::cout << "Animal action" << std::endl;
}
static play::override<play_animal> override_play_animal;

void play_cat(virtual_ptr<Cat> cat) {
	play_animal(cat);
	std::cout << "Cat action" << std::endl;
	cat->actions += 1;
}
static play::override<play_cat> override_play_cat;

void play_dog(virtual_ptr<Dog> dog) {
	play_animal(dog);
	std::cout << "Dog action" << std::endl;
	dog->actions += 1;
}
static play::override<play_dog> override_play_dog;

void play_bulldog(virtual_ptr<Bulldog> bulldog) {
	play_dog(bulldog);
	play::next<play_bulldog>(bulldog);
	std::cout << "Bulldog action" << std::endl;
	bulldog->actions += 1;
}
static play::override<play_bulldog> override_play_bulldog;


int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> felix(new Cat("Felix"));
	std::unique_ptr<Animal> snoopy(new Dog("Snoopy"));
	std::unique_ptr<Animal> hector(new Bulldog("Hector"));

	play::fn(*felix);
	std::cout << felix->actions << std::endl;

	play::fn(*snoopy);
	std::cout << snoopy->actions << std::endl;

	play::fn(*hector);
	std::cout << hector->actions << std::endl;

	return 0;
}
