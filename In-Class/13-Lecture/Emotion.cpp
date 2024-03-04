#include <iostream>
#include <string>

#include "Emotion.h"

std::ostream& operator<<(std::ostream &os, const Emotion &d) {
    os << d.get_name();
    // TODO: print out more information if you want to
    return os;
}

Emotion * EmotionFactory::GetHappy() {
    return new Emotion("Happy", true, false, 0.5, 0.5, 0.5);
}

Emotion * EmotionFactory::GetAngry() {
    return new Emotion("Angry", false, false, 0.3, 0.9, 0.9);
}

Emotion * EmotionFactory::GetBored(){
    return new Emotion("Bored", true, false, 0.7, 0.2, 0.55);
}