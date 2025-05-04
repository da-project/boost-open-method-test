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

BOOST_OPENMETHOD(poke, (std::ostream&, virtual_ptr<const Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(poke, (std::ostream & os, virtual_ptr<const Cat> cat), void) {
	os << cat->name << " hisses";
}

BOOST_OPENMETHOD_OVERRIDE(poke, (std::ostream & os, virtual_ptr<const Dog> dog), void) {
	os << dog->name << " barks";
}

BOOST_OPENMETHOD_OVERRIDE(poke, (std::ostream & os, virtual_ptr<const Bulldog> dog), void) {
	next(os, dog);
	os << " and bites back";
}


int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> felix(new Cat("Felix"));
	std::unique_ptr<Animal> snoopy(new Dog("Snoopy"));
	std::unique_ptr<Animal> hector(new Bulldog("Hector"));

	//////////////////////////////////////////////////////////////
	poke(std::cout, *felix); // Felix hisses
	std::cout << ".\n";

	poke(std::cout, *snoopy); // Snoopy barks
	std::cout << ".\n";

	poke(std::cout, *hector); // Hector barks and bites
	std::cout << ".\n";

	const Cat matou("Matou");

	poke(std::cout, matou);
	std::cout << ".\n";

	return 0;
}
