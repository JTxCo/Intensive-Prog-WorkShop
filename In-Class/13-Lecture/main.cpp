#include <iostream>
#include <vector>

#include "Emotion.h"
#include "Creature.h"

// Names:
//
//


int main() {
    // 4) in main.cpp, get pointers to your emotions and Infect some Creature objects (how many of each is up to you)
    // (the rest of the work for this part will take place in main.cpp)
    EmotionFactory ef;
    Emotion * happy = ef.GetHappy();
    Emotion * angry = ef.GetAngry();
    Emotion * bored = ef.GetBored();
    // Part 1 (factory) 
    // ---------------
    // 4) get pointers to one of each type of your Emotion objects via your EmotionFactory. Then,
    // call the Emotion's get_count method to see how many Emotion objects have been instantiated.
    std::cout << happy->get_count() << std::endl;
    std::cout << angry->get_count() << std::endl;
    std::cout << bored->get_count() << std::endl;
    // 5) are your EmotionFactory's Get____() methods static or non-static? Do you think that they should
    // be one or the other? Justify your answer. If your methods are static, what would change if they were
    // non-static? If they are non-static, what would change if they were static?

    // methods are non staticb because they are not getting a static variable from the class.


    // 6) Feel free to create more creatures here
    Creature original_creature(14);
    Creature unoriginl_creature(21);
    // 7) Infect your creatures with your emotions. Test out the Creature Spread method.

    for(Emotion * d : original_creature.get_emotions() ) {
        std::cout << *(d) << std::endl;     `
    }

    original_creature.AddEmotion(happy);
    original_creature.AddEmotion(angry);
    original_creature.AddEmotion(bored);

    original_creature.Spread(&unoriginl_creature);

    for (Emotion * d : unoriginl_creature.get_emotions() ) {
        std::cout << *(d) << std::endl;     
    }

    // STOP! Turn in Emotion.h, Emotion.cpp, and main.cpp on canvas

 
    // Part 2 (prototype) 
    // ---------------
    Creature * c = original_creature.Clone();
    Creature * c2 = unoriginl_creature.Clone();

    kidCreature kc(3);
    kidCreature * kc2 = kc.Clone();


    // 3) Create some new Creature * objects by using the Creature's Clone() method. Does this method use dynamic dispatch?
    // Answer:
    // How did you test this?
    Creature * c3 = kc.Clone();
    // It is using the method that is in the kidCreature class because of the virtual keyword in the Creature class.


    // If you finish:
    // -------------
    // 4) Write a new function in this file void ScienceLab(Creature * original) (not associated with any classes)
    // that takes an original creature and conducts experiments by cloning it and measuring the spread of emotion.
    // You have complete creative freedom here. Feel free to add methods to the Emotion/Creature classes.
    // (The only requirements are the function definition and that you must call Clone() within that function).
    //
    // Call your ScienceLab function as many times as is necessary for your experiments.
    // void ScienceLab(Creature * original){

    // }



}

