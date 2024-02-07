#include <iostream>
#include <string>

#include "Animal.h"

void Animal::Race(Animal &opponent) {
	// first animal wins ties
	std::cout << this->GetSpeed() << std::endl;
	std::cout << opponent.GetSpeed() << std::endl;
	if (this->GetSpeed() >= opponent.GetSpeed()) {
		std::cout << this->MakeSound() << std::endl;
	} else {
		std::cout << opponent.MakeSound() << std::endl;
	}
}

