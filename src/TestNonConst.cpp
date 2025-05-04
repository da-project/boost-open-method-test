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

BOOST_OPENMETHOD_CLASSES(Animal, Cat, Dog, Bulldog);

BOOST_OPENMETHOD(play, (virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(play, (virtual_ptr<Animal> animal), void) {
	std::cout << "Animal action" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(play, (virtual_ptr<Cat> cat),	void) {
	std::cout << "Cat action" << std::endl;
	cat->actions += 1;
}

BOOST_OPENMETHOD_OVERRIDE(play, (virtual_ptr<Dog> dog), void) {
	std::cout << "Dog action" << std::endl;
	dog->actions += 2;
}

BOOST_OPENMETHOD_OVERRIDE(play, (virtual_ptr<Bulldog> dog), void) {
	std::cout << "Bulldog action" << std::endl;
	next(dog); // call base overrider
	dog->actions += 1;
}


int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> felix(new Cat("Felix"));
	std::unique_ptr<Animal> snoopy(new Dog("Snoopy"));
	std::unique_ptr<Animal> hector(new Bulldog("Hector"));

	//////////////////////////////////////////////////////////////
	play(*felix);
	std::cout << felix->actions << std::endl;

	play(*snoopy);
	std::cout << snoopy->actions << std::endl;

	play(*hector);
	std::cout << hector->actions << std::endl;

	const Cat cat("Image");

	//play(cat); // Compilation error :)

	return 0;
}
