#include <iostream>

#include "Animal.h"

// Name(s):

void animalWinner(Animal *animals[]){
  int winner = 0;
  int speed = 0;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (i != j){
        if (animals[i]->GetSpeed() > animals[j]->GetSpeed()){
          if (animals[i]->GetSpeed() > speed){
            speed = animals[i]->GetSpeed();
            winner = i;
          }
        }
        else{
          if (animals[j]->GetSpeed() > speed){
            speed = animals[j]->GetSpeed();
            winner = j;
          }
        }
      }
    }
  }
  std::cout << "The winner is: " << animals[winner]->MakeSound() << std::endl;
}


int main() {

  Reptile ralph("alligator");
  // std::cout << ralph.MakeSound() << std::endl;

  // 1) Instantiate another animal
  Animal dog("woof");
  // 2) Call the Fight method of animal
  // dog.Race(ralph);
  // 3) Go to the Animal.h file and define some new subclasses of animal
  // Define one class that inherits from Animal and
  // one class that inherits from a child class of Animal

  // 4) Instantiate at least one object of each class you defined for #3
  Bird robin("tweet");
  Penguin penguin("squawk");

  // 5) Have a tournament between the animals that you have instantiated
  // dog.Race(robin);
  // dog.Race(penguin);
  // ralph.Race(robin);
  // ralph.Race(penguin);
  // robin.Race(penguin);
  // robin.Race(ralph);
  // robin.Race(dog);
  // penguin.Race(ralph);
  // penguin.Race(dog);
  // penguin.Race(robin);



  // 6) 1. Create a list of Animal pointers with at least one of each type of Animal you created
  Animal *animals[4] = {&ralph, &dog, &robin, &penguin};



// 7). 2. Write a function that takes this list as an argument and runs a race between all combinations of these Animals, printing the results and the winner of the combined races.
  animalWinner(animals);
}
