#include <iostream>

#include "Animal.h"

// Name(s):

int main() {

  Reptile ralph("alligator");
  std::cout << ralph.MakeSound() << std::endl;

  // 1) Instantiate another animal
  Animal dog("woof");
  // 2) Call the Fight method of animal
  dog.Race(ralph);
  // 3) Go to the Animal.h file and define some new subclasses of animal
  // Define one class that inherits from Animal and
  // one class that inherits from a child class of Animal

  // 4) Instantiate at least one object of each class you defined for #3
  Bird robin("tweet");
  Penguin penguin("squawk");

  // 5) Have a tournament between the animals that you have instantiated
  dog.Race(robin);
  dog.Race(penguin);
  ralph.Race(robin);
  ralph.Race(penguin);
  robin.Race(penguin);
  robin.Race(ralph);
  robin.Race(dog);
  penguin.Race(ralph);
  penguin.Race(dog);
  penguin.Race(robin);

	return 0;
}
