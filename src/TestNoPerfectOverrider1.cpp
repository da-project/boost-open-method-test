#include <boost/openmethod.hpp>
#include <boost/openmethod/compiler.hpp>

#include <iostream>

struct Animal {
	Animal(std::string name) :
		name(name) {
	}
	std::string name;
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

void play_cat(virtual_ptr<Cat> cat) {
	std::cout << "Cat action" << std::endl;
}
static play::override<play_cat> override_play_cat;

void play_dog(virtual_ptr<Dog> dog) {
	std::cout << "Dog action" << std::endl;
}
static play::override<play_dog> override_play_dog;

void play_animal(virtual_ptr<Animal> animal) {
	std::cout << "Animal action" << std::endl;
}
static play::override<play_animal> override_play_animal;


int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> felix(new Cat("Felix"));
	std::unique_ptr<Animal> snoopy(new Dog("Snoopy"));
	std::unique_ptr<Animal> hector(new Bulldog("Hector"));

	play::fn(*felix);
	play::fn(*snoopy);
	play::fn(*hector); // play_dog is called, choice does not depend on the order of definition

	return 0;
}
