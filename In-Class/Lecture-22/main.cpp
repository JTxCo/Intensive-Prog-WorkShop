#include <iostream>

/**
  MIDTERM REVIEW

  This file contains tasks 1-7 to help you review for the midterm, which will include
  short answer questions about the code and require you to write code snippets (closed note).

  Please ask questions if you need clarification on any of the following tasks.
*/
using std::cout;
using std::endl;
class Bike
{
public:
  Bike()
  {
    bike_id_ = id_generator_++;
    wheels_ = 2;
    gears_ = 5;
  }
  Bike(const Bike& other)
  {
    // Copy data from the other Bike
    wheels_ = other.wheels_;
    gears_ = other.gears_;

    // Assign a new ID
    bike_id_ = id_generator_++;
  }
  Bike(int wheels, int gears)
  {
    bike_id_ = id_generator_++;
    wheels_ = wheels;
    gears_ = gears;
  }
  void virtual pedal(){
    gears_ = 1;
    wheels_ = 2;
    std::cout << "I want to ride my Bicycle" << std::endl;
  };
  void printBikeID()
  {
    std::cout << "Bike ID: " << bike_id_ << std::endl;
  }
  friend std::ostream& operator<< (std::ostream& out, const Bike& bike){
    out << "Bike " << bike.bike_id_ << "(" << bike.wheels_ << " wheels, " << bike.gears_ << " gears" << ')';

    return out;
   }
  //using the copy constructor
  
private:
  static int id_generator_;
  int bike_id_;
  int wheels_;
  int gears_;
};
int Bike::id_generator_ = 0;
// Leave this commented out until Task 5
// Operator overloading resource: https://www.learncpp.com/cpp-tutorial/overloading-the-io-operators/
// std::ostream& operator<< (... add params ...)
// {
//     out << "Bike " << bike_id_ << "(" << bike.wheels_ << " wheels, " << bike.gears_ << " gears" << ')';

//     return out;
// }

class Tricycle : public Bike {
  private:
    int wheels_;
    int gears_;
  public:
    Tricycle() {
      wheels_ = 3;
      gears_ = 1;
    }
    void  pedal()  {
      wheels_ = 3;
      gears_ = 1;
      std::cout << "I want to ride my Tricycle" << std::endl;
    }

    // friend std::ostream& operator<< (std::ostream& out, Bike & trike){
    //   out << "Tricycle " << trike.bike_id_ << "(" << trike.wheels_ << " wheels, " << trike.gears_ << " gears" << ')';
    //   return out;
    // }

};

// Task 2
template <typename T>
void swap(T &a, T &b)
{
  T temp = a;
  a = b;
  b = temp;
}

int main() 
{
  // Task 1a: Which of the following are references? How are they different from pointers?
  //e is a reference, c and d are pointers


  int a = 100; 
  int b = 200;
  int * c = &a;
  int * d = &b;
  int & e = a;
  // Task 1b: Describe in a comment what is happening on the following line:
  //the location of the pointer c is being changed to the location of the pointer d
  c = d;
  
  
  // Task 2: Write function calls to swap using various variable types.
  // See if you can get any of them to behave unexpectedly. 
  // Write comments describing a case you expected to work but didn't
  // and try to find out why.

  
  swap(a, b);//values of a and b are swapped 100 -> 200, 200 -> 100
  // cout<<c<<endl;//prints the location of the pointer c
  swap(c, d);//since c got set to the location of d,  nothing will happen
  // cout<<c<<endl;//prints the location of the pointer d
  swap(e, a);//since e is a reference to a, the values of a and e will be swapped, but nothing will happen to the value outputted
  
  swap(e, b); //it was 200 before but now it will be 100 because of earlier swap 
  
  //swap(c,e); this will not work because c is a pointer and e is a reference

  swap(*c, e);//this will work because c is being dereferenced and e is a reference to a

  // Task 3a: initialize Bike's id field to 0 and add code
  // to increment it any time a bike is created.
  // Task 3b: How many bike objects are created from the following lines of code?
 //29
  Bike bikeShopInventory[25];
  Bike * myTownie = new Bike();
  Bike yourTownie(bikeShopInventory[0]);
  Bike hisTownie = *myTownie;
  Bike * herTownie = myTownie;
  Bike myMtnBike;
  myMtnBike.printBikeID();
  bikeShopInventory[0].printBikeID();

  // Task 3c: Does your id get incremented appropriately for the number of bike objects created?
  //no it does not
  // Task 3d: Label the lines o f code abover where the assignment operator and copy constructor are used.
  // (hint: we talked about these in the Singleton lecture with the Earth class)
  //now it works with teh copy constuctor 


  // Task 4a: Modify the Bicycle and Tricycle classes above
  // using the virtual and override keywords to get the trike_pointer to use the Tricycle class's pedal()
  Tricycle trike;
  trike.pedal();
  cout<<trike<<endl;
  Bike * trike_pointer = &trike;
  trike_pointer->pedal();
  // Task 4b: Is the pedal function an example of function overriding or overloading? overriding 
  // Task 4c: Is is compile-time or runtime polymorphism? why? runtime because the function is being called at runtime
  // Task 4d: Add a constructor to Bike that takes a specific number of gears and wheels as parameters
  // Create a bike object that uses this constructor.
  Bike daBike(4, 6);
  // Task 4e: Is this an example of function overriding or overloading? overloading
  // Task 4f: Is it compile-time or runtime polymorphism? why? compile time because the function is being called at compile time

  // Task 5a: comment out the following line. Do you get an error? Why? no but it is used to print out the bike object
  std::cout << trike << std::endl;
  // Task 5b: Fix the error by commenting out the << operator overload function above, adding in the
  // appropriate function arguments
  // Task 5c: Why do we use the friend keyword in this case? so it can access the private members of the class
  // Task 5d: Is operator overloading an example of compile-time or runtime polymorphism? compile time because the function is being called at compile time 


  // Task 6: Pick 2 of the following design patterns and explain with an example the purpose
  // of using that design pattern (no code necessary)
  // 1. Singleton one instance of a class, ex: one databse connection
  // 2. Factory: creates objects without specifying the exact class of object that will be created, ex: a car factory
  // 3. Prototype: creating new objects by copying an existing object, ex: different chair designs
  // 4. Flyweight: minimizes memory usage or computational expenses by sharing as much as possible with related objects, ex: a text editor fonts

  // Task 7: Add one additional button to one of your Qt project and connect it with the main
  // windows signal to refresh your memory on this process.
}