#include <iostream>
#include <math.h>
using namespace std;


class Food {
    public:

    // int energy;
    int nutrients_left;
    int min_size;
    int nibble_size;
    int x;
    int y;
    int size;
    double energy_returned_percentage;

    bool deleted = false;

    bool is_in_range(int cx, int cy) {
        
        int left_x = x - size;
        int right_x = x + size;
        int bottom_y = y - size;
        int top_y = y + size;
        
        if (cx < max(right_x, left_x) && cx > min(right_x, left_x) && cy < max(top_y, bottom_y) && cy > min(top_y, bottom_y)) {
            return true;
        }
        return false;
    }

    auto give_food(int animal_size) {
        struct retGain{
            int size_gain;
            double energy_gain;
        };

        int size_gained = 0;
        double energy_given = energy_returned_percentage;

        // Animal can deplete this food source
        if (animal_size > min_size) { 
            nutrients_left = 0;
            return retGain{nutrients_left, energy_given};

        // Animal is too small, an must nibble on this food source
        } else {
            nutrients_left = nutrients_left - nibble_size;
            return retGain{nibble_size, energy_given};
        }
    }

};
