#ifndef EARTH_H
#define EARTH_H
#include <iostream>
using std::string;
class Earth {
public:
	
	static Earth& GetInstance() {
		// gets instantiated the first time
		static Earth instance; // guaranteed to be destroyed

		return instance;
	}

    int get_population() { return population_; };

    void IncreasePopulation() { population_ += 1; };

	// Delete the methods we don't want

	friend ostream &operator<<(ostream &os, const Earth &earth) {
		os << "Earth's population is: " << earth.population_;
		return os;
	}
	string name = "Earth";
 private:
 	Earth();  // private constructor

    int population_;
  
};  // class Earth

#endif  // EARTH_H

