#include <iostream>
#include "Earth.h"


using std::cout;
using std::endl;
// Names:
//

int main(int argc, char **argv){
    // 0) Implement your Earth's constructor in Earth.cpp
    // 1) Get an instance of your earth object
    Earth &earth = Earth::GetInstance();
    // 2) Get another instance of your earth object
    Earth &earth2 = Earth::GetInstance();
    // 3) Test to see if the two Earth instances from #1 and #2 are stored at the same
    // location in memory.
    if(&earth == &earth2){
        std::cout << "The two Earth instances are stored at the same location in memory." << std::endl;
    } else {
        std::cout << "The two Earth instances are stored at different locations in memory." << std::endl;
    }
    // 3) Call IncreasePopulation from one of your Earth instances. Can you see this change
    // from your other Earth instance?
    cout<<"earth pop: "<<earth.get_population()<<endl;
    cout<<"earth2 pop: "<<earth2.get_population()<<endl;
    earth.IncreasePopulation();
    cout<<"earth pop: "<<earth.get_population()<<endl;
    cout<<"earth2 pop: "<<earth2.get_population()<<endl;
    // You can see the pop change in both of them
    // 4) Create a public field in your Earth object. Do you need an instance of an Earth object
    // to access this field?
    cout<<earth.name<<endl;



    // create instances of Earth but deleted:
    // Earth(Earth const&) = delete; // copy constructor
	// void operator=(Earth const&) = delete; // assignment operator
    Earth* earth4 = &Earth::GetInstance();
    earth4->IncreasePopulation();
    cout << "earth pop: " << earth4->get_population() << endl;
    cout<<"earth pop: "<<earth4->get_population()<<endl;
	return 0;
}
