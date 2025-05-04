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

BOOST_OPENMETHOD_CLASSES(Animal, Cat, Dog, Bulldog);

BOOST_OPENMETHOD(fun, (virtual_ptr<Animal>), Animal);

BOOST_OPENMETHOD_OVERRIDE(fun, (virtual_ptr<Cat> cat), Cat) {
	return Cat("Billi");
}

BOOST_OPENMETHOD(funp, (virtual_ptr<Animal>), Animal*);

BOOST_OPENMETHOD_OVERRIDE(funp, (virtual_ptr<Cat> cat), Cat*) {
	return cat.get();
}


int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> felix(new Cat("Felix"));

	// fun
	Animal a = fun(*felix);
	std::cout << a.name << std::endl;

	// funp
	Animal* pa = funp(*felix);
	std::cout << pa->name << std::endl;

	pa = funp(funp(*felix));
	std::cout << pa->name << std::endl;

	return 0;
}
