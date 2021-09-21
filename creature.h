#include <iostream>
#include "global.h"
#include <math.h>
// #include <global.h>

using namespace std;


class Creature {
    public:

    int x;
    int y;

    double speed = 1;

    double size = 1;
    
    int generation = 1;
    double splitting_factor = 1;

    double cur_energy = 250;
    double max_energy = 250;

    Food *target; // Null reference

    double distx = 0;
    double disty = 0;
    double distdiag = 0;
    double energy_unit = 0;

    double xstep = 0;
    double ystep = 0;
    double diagstep = 0;

    double energyDrainStep = 0;

    bool check_target() {
        return target->nutrients_left > 0;
    }

    void lock_on_to_target(){
        
        if (creature_debug) {cout << "Target location is found as... " << target->x << ", " << target->y << "\n";}

        int x1 = target->x;
        int x2 = x;

        int y1 = target->y;
        int y2 = y;

        distx = target->x - x;
        disty = target->y - y;
        distdiag = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

        // The energy unit is designed to mark how far it would take the creature to travel one relative-sized body length on the map. 
        // The angle traveled*speed will determine how far they travel
        // This is then divided by the energy_unit to determine energy drain
        energy_unit = sqrt(pow(size, 2) + pow(size, 2));        // Convert distance into terms of energy units
        double total_drain_to_target = distdiag/energy_unit;    // Total amount of energy to trave distance
        int moves_till_arrival = ceil(distdiag/(size*speed));   // Turns needed to make this trip
        double drain_per_move = total_drain_to_target/moves_till_arrival;   // Energy drained each move
        double distance_travelled_per_move = drain_per_move * energy_unit;  // Distance Traveled Per Move

        xstep = distx/moves_till_arrival;
        ystep = disty/moves_till_arrival;
        diagstep = abs(distance_travelled_per_move);
        energyDrainStep = abs(drain_per_move);
    }

    Food get_target() {
        return *target;
    }

    auto make_turn() {
        struct retVals {
            bool isSplittable;
            bool foodLeft;
        };

        bool isSplittable = false;
        bool foodLeft = target->nutrients_left > 0;;

        if (!attempt_eat()) {
            return retVals{false, foodLeft};

        } else {
            isSplittable = size > splitting_factor;
            return retVals{isSplittable, foodLeft};
        }
    }
    
    void move() {
        
        cur_energy = cur_energy - energyDrainStep;

        // acknowledge you are getting closer
        distdiag = distdiag - diagstep;
        distx = distx - xstep;
        disty = disty - ystep;
        
        x = x + xstep;
        y = y + ystep;
    }

    bool attempt_eat() {
        // return if the food has been depleted

        // if (creature_debug) {cout << "Creature @ (" << x <<", " << y << ") trying to eat.\n";}

        if (target->is_in_range(x, y)) {
            if (creature_debug) {cout << "\tCreature @ (" << x <<", " << y << ") is eating. (Size=" << size << ")\n";}

            auto retVal =  target->give_food(size);
            int size_gained = retVal.size_gain;
            
            size = size + size_gained;
            cur_energy = cur_energy + (max_energy * retVal.energy_gain);

            if (cur_energy > max_energy) {
                if (creature_debug) {cout << "\t\tCreature @ (" << x <<", " << y << ") is full of energy.\n";}
                cur_energy = max_energy;
            }
            
            if (creature_debug) {cout << "Creature @ (" << x <<", " << y << ") Gained " << (max_energy * retVal.energy_gain) << " energy & " << size_gained << " size.\n";}

            return true; // food eaten successfully
        }
        return false;      // This method should not be called here. Only call when ontop of edible food.
    }

    bool is_drained() {
        return cur_energy <= 0;
    }

    auto split_creature() {
        struct children {
            Creature child1;
            Creature child2;
        };


        if (splitting_debug) {cout << "Creature @ (" << x <<", " << y << ") is splitting into two sub creatures.\n"
             << "\tSize: (" << size << ") || Splitting Factor: " << splitting_factor << "\n"
             << "\tSpeed " << speed << "\n"
             << "\tHunting Coordinates: ( >" << x << ", ^" << y << ") -> ( >" << target->x << ", ^" << target->y << ")\n"
             << "\tDistance Vector: ( >" << distx << ", ^" << disty << ", >^" << distdiag << ")\n"
             << "\tStep Vector: ( >" << xstep << ", ^" << ystep << ", >^" << diagstep << ")\n"
             <<"\tTurns Until Target Reach: " << distdiag/diagstep << "\n"
             << "\tGeneration: " << generation << "\n";
             
            int x;
            cin >> x;
        }
        else {
            cout << "New generation @ (" << x <<", " << y << "):\t\t" << (generation + 1) << "\n";
        }
        int next_generation = generation + 1;
        Creature child1{x, y, speed, size/2, next_generation, splitting_factor, max_energy/2, max_energy};
        Creature child2{x, y, speed, size/2, next_generation, splitting_factor, max_energy/2, max_energy};
        

        
        return children{child1, child2};
    }

};