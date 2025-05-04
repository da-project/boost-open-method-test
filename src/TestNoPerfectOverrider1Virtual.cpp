#include <boost/openmethod.hpp>
#include <boost/openmethod/compiler.hpp>

#include <iostream>

struct Animal {
	Animal() {}
	Animal(std::string name) :
		name(name) {
	}
	std::string name;
	virtual ~Animal() = default;
};

struct Cat: virtual Animal {
	Cat() {}
	using Animal::Animal;
};

struct Dog: virtual Animal {
	Dog() {}
	using Animal::Animal;
};

struct Chimera: Cat, Dog {
	Chimera(std::string name) :
		Animal(name) {
	}
};

struct Bulldog: Dog {
	Bulldog() {}
	using Dog::Dog;
};

struct Bullchimera: Cat, Bulldog {
	Bullchimera(std::string name) :
		Animal(name) {
	}
};


using namespace boost::openmethod;

static use_classes<Animal, Cat, Dog, Bulldog, Chimera, Bullchimera> animal_classes;


namespace catdog {

class play_openmethod;

using play = method<play_openmethod(virtual_ptr<Animal>), void>;

void play_bulldog(virtual_ptr<Bulldog> bulldog) {
	std::cout << "Bulldog action" << std::endl;
}
static play::override<play_bulldog> override_play_bulldog;

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

}


namespace dogcat {

class play_openmethod;

using play = method<play_openmethod(virtual_ptr<Animal>), void>;

void play_dog(virtual_ptr<Dog> dog) {
	std::cout << "Dog action" << std::endl;
}
static play::override<play_dog> override_play_dog;

void play_cat(virtual_ptr<Cat> cat) {
	std::cout << "Cat action" << std::endl;
}
static play::override<play_cat> override_play_cat;

void play_animal(virtual_ptr<Animal> animal) {
	std::cout << "Animal action" << std::endl;
}
static play::override<play_animal> override_play_animal;

void play_bulldog(virtual_ptr<Bulldog> bulldog) {
	std::cout << "Bulldog action" << std::endl;
}
static play::override<play_bulldog> override_play_bulldog;


}

int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> felix(new Cat("Felix"));
	std::unique_ptr<Animal> snoopy(new Dog("Snoopy"));
	std::unique_ptr<Animal> chimera(new Chimera("Chimera"));
	std::unique_ptr<Animal> bullchimera(new Bullchimera("Bullchimera"));


	catdog::play::fn(*felix);
	dogcat::play::fn(*felix);

	std::cout << std::endl;

	catdog::play::fn(*snoopy);
	dogcat::play::fn(*snoopy);

	std::cout << std::endl;

	catdog::play::fn(*chimera); // Ambiguity, choice of override (Cat or Dog) depends on the definition order
	dogcat::play::fn(*chimera); // Ambiguity, choice of override (Cat or Dog) depends on the definition order

	std::cout << std::endl;

	catdog::play::fn(*bullchimera); // Idem
	dogcat::play::fn(*bullchimera); // Idem

	return 0;
}
