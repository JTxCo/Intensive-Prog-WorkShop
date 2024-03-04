#include <string>
#include <vector>

#include "Emotion.h"
#include "Creature.h"


void Creature::Spread(Creature * c2) {
    srand( time(0) );
    for (Emotion * d : this->get_emotions()) {
        if (d->get_is_communicable()) {
            int age = c2->get_age();
            double rand_chance = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            if ((age < 20 && rand_chance < d->get_affects_young_rate()) ||
                (age >= 20 && age < 60 && rand_chance < d->get_affects_middle_aged_rate()) ||
                (age >= 60 && rand_chance < d->get_affects_old_rate())) { 
                c2->AddEmotion(d);  
            }
        }
    }
}

