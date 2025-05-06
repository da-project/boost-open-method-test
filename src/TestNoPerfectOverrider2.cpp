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

namespace pm {

BOOST_OPENMETHOD(encounter, (virtual_ptr<Animal>, virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Bulldog>, virtual_ptr<Bulldog>), void) {
    std::cout << "Bulldog Bulldog" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Bulldog>), void) {
    std::cout << "Animal Bulldog" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Dog>, virtual_ptr<Animal>), void) {
    std::cout << "Dog Animal" << std::endl;
}

}

namespace ad_da {

BOOST_OPENMETHOD(encounter, (virtual_ptr<Animal>, virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Dog>), void) {
    std::cout << "Animal Dog" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Dog>, virtual_ptr<Animal>), void) {
    std::cout << "Dog Animal" << std::endl;
}

}

namespace da_ad {

BOOST_OPENMETHOD(encounter, (virtual_ptr<Animal>, virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Dog>, virtual_ptr<Animal>), void) {
    std::cout << "Dog Animal" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Dog>), void) {
    std::cout << "Animal Dog" << std::endl;
}

}

namespace da_ab {

BOOST_OPENMETHOD(encounter, (virtual_ptr<Animal>, virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Dog>, virtual_ptr<Animal>), void) {
    std::cout << "Dog Animal" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Bulldog>), void) {
    std::cout << "Animal Bulldog" << std::endl;
}

}

namespace ab_da {

BOOST_OPENMETHOD(encounter, (virtual_ptr<Animal>, virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Bulldog>), void) {
    std::cout << "Animal Bulldog" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Dog>, virtual_ptr<Animal>), void) {
    std::cout << "Dog Animal" << std::endl;
}

}

namespace ab_da_ad {

BOOST_OPENMETHOD(encounter, (virtual_ptr<Animal>, virtual_ptr<Animal>), void);

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Dog>, virtual_ptr<Animal>), void) {
    std::cout << "Dog Animal" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Bulldog>), void) {
    std::cout << "Animal Bulldog" << std::endl;
}

BOOST_OPENMETHOD_OVERRIDE(encounter, (virtual_ptr<Animal>, virtual_ptr<Dog>), void) {
    std::cout << "Animal Dog" << std::endl;
}

}

int main(int arg, char *argv[]) {

	boost::openmethod::initialize();

	std::unique_ptr<Animal> hector(new Bulldog("Hector"));

	pm::encounter(*hector, *hector); // Perfect match

	std::cout << std::endl;

	ad_da::encounter(*hector, *hector); // Ambiguity, choice of override depends on the definition order
	da_ad::encounter(*hector, *hector); // Ambiguity, choice of override depends on the definition order

	std::cout << std::endl;

	da_ab::encounter(*hector, *hector); // Ambiguity, choice of override depends on the definition order
	ab_da::encounter(*hector, *hector); // Ambiguity, choice of override depends on the definition order
	ab_da_ad::encounter(*hector, *hector);

	return 0;
}
