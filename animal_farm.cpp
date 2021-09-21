#include <iostream>
#include <math.h>
#include <list>
#include <queue>          // std::queue
#include <random>
#include <iomanip>

// #include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Food.h"
#include "creature.h"
#include "global.h"
#include "output_commands.cpp"

// using namespace std;
using std::setprecision;


Food* find_closest_food(queue<Food *> food_queue, int x, int y){

    Food *startvation;
    if (food_queue.size() == 0) {
        // cout << "\n\n\n**********************************\n STARVATION \n ***********************************\n\n\n";
        // cin >> x;
        // throw invalid_argument("Food_queue is empty during closest search!");
        startvation = new Food{10, int(max_size), 0, x, y, 15, 0};
        return startvation;
    }
    
    double closest_diag = 276447232;
    Food *closest_food;
    if (creature_debug) {cout << "\n\n SEARCHING FOR NEW CREATURE...\n";}

    for (int i = 0; i < food_queue.size(); i++) {

        Food *f = food_queue.front();
        double distdiag = sqrt((f->x-x)*(f->x-x) + (f->y-y)*(f->y-y));

        if (distdiag < closest_diag && f->nutrients_left > 0) {
            //if (creature_debug) { cout << "NEW FOOD FOUND @ " << f->x << ", " << f->y << " (" << distdiag << " < " << closest_diag << ")\n";}
            closest_food = f;
            closest_diag = distdiag;
        }
        
        // Move through queue
        food_queue.pop();
        food_queue.push(f);
    }

    if (creature_debug) {cout << "CLOSEST FOOD LOCATED @ " << closest_food->x << ", " << closest_food->y << "\n";}
    
    return closest_food;
}

queue<Food *> remove_food(queue<Food *> food_list, Food *to_be_deleted) {
    for (int i = 0; i< food_list.size(); i++) {
        Food * f = food_list.front();
        food_list.pop();
        if (f->x != to_be_deleted->x || f->y != to_be_deleted->y) {
            food_list.push(f);  // not the wanted food
        } else {
            f->deleted = true;
            break;  // The food has been found & deleted
        }
    }
    return food_list; // return modified food list
}
void delete_food(queue<Food *> food_list) {
    for (int i = 0; i< number_of_food_per_round; i++) {
        Food *f = food_list.front();
        delete(&f);        
    }
}




void test_scripts(queue<Food *> food_list, queue<Creature> creature_list) {
    // Test loop
    if (food_debug) {if (food_debug) {food_data_full(food_list);}}
    if (creature_debug) {animal_data_condensed(creature_list);}

    for (int i = 0; i< food_list.size(); i++) {

        Food *f = food_list.front();
        
        f->nutrients_left = -1;

        food_list.pop();
        food_list.push(f);
    }

    if (food_debug) {food_data_full(food_list);}
    if (creature_debug) {animal_data_condensed(creature_list);}
    
}


void main_script(queue<Food *> food_list, queue<Creature> *creature_list) {
    
    int i = -1;
    int k = 0;
    int j = 0;

    int number_of_splits = 0;
    int number_of_food_eaten = 0;

    while(creature_list->size() > 0) {
        
        i++;
        k = i%creature_list->size();
        j = i/creature_list->size();

        if (i >= number_of_iterations) {
            break;
        }
        // if (food_list.size() == 0) {
        //     cout << "\n\n\n**********************************\n STARVATION \n ***********************************";
        // }

        // cout << "\n\nMove " << j << " for creature " << k << ".....\n";

        Creature c = creature_list->front();

        auto retVals = c.make_turn();
        bool splitting_factor_reached = retVals.isSplittable;
        bool food_left = retVals.foodLeft;

    
        if (splitting_factor_reached) {  // The creatures end of turn will be spend splitting into two.
            
            number_of_splits++;

            auto retVal = c.split_creature();
            creature_list->pop();
            
            Creature first_split = retVal.child1;
            Creature second_split = retVal.child2;
        
            Food *closest_food_ptr1 = find_closest_food(food_list, first_split.x, first_split.y);
            first_split.target = closest_food_ptr1;
            first_split.lock_on_to_target();
            creature_list->push(first_split);

            Food *closest_food_ptr2 = find_closest_food(food_list, second_split.x, second_split.y);
            second_split.target = closest_food_ptr2;
            second_split.lock_on_to_target();
            creature_list->push(second_split);

        } else if (!food_left) {    // Food source has run out. Removing food from food list;

            number_of_food_eaten++;

            if (!c.target->deleted) {
                food_list = remove_food(food_list, c.target);
                if (food_debug){
                   if (food_debug) { cout << "\n\n\n**********************************\n FOOD DESTROYED. \n ***********************************\n\n";}
                }
                
            }


            Food *closest_food_ptr = find_closest_food(food_list, c.x, c.y);
            c.target = closest_food_ptr;
            c.lock_on_to_target();
            
            creature_list->pop();
            creature_list->push(c);

        } else if (c.is_drained()) { // The creature has died without eating.
        if (creature_debug) {
            cout << "Creature " << k << " has perished. \n\tEnergy : (" << c.cur_energy << "/" << c.max_energy << ")\n"
             << "X: " << c.x << " Y: " << c.y << "\n"
             << "\tSize: (" << c.size << ") || Splitting Factor: " << c.splitting_factor << "\n"
             << "\tSpeed " << c.speed << "\n"
             << "\tHunting Coordinated: ( >" << c.x << ", ^" << c.y << ") -> ( >" << c.target->x << ", ^" << c.target->y << ")\n"
             << "\tDistance Vector: ( >" << c.distx << ", ^" << c.disty << ", >^" << c.distdiag << ")\n"
             << "\tStep Vector: ( >" << c.xstep << ", ^" << c.ystep << ", >^" << c.diagstep << ")\n"
             <<"\tTurns Until Target Reach: " << c.distdiag/c.diagstep << "\n"
             << "\tGeneration: " << c.generation << "\n";
        }
            creature_list->pop();

            i = 0;
            
            int k;
            if (creature_debug) {cin >> k;}

        } else { // The creature has only moved.
            c.move();
            creature_list->pop();
            creature_list->push(c);
        }   
    }
}



void run_animal_house(int num_creat, int num_food, int avg_size){
    // Taken from https://www.delftstack.com/howto/cpp/how-to-generate-random-doubles-cpp/
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> location_start_xrange(1, map_width-1);
    std::uniform_real_distribution<double> location_start_yrange(1, map_height-1);

    std::uniform_real_distribution<double> size_range(min_size, max_start_size);
    std::uniform_real_distribution<double> splitting_range(min_splitting_factor, max_splitting_factor);
    std::uniform_real_distribution<double> speed_range(min_speed, max_speed);
    
    
    std::uniform_real_distribution<double> food_chance(0, 1);
    std::uniform_real_distribution<double> food_size_range(15, 45);


    setprecision(2);
    
    queue<Creature> creature_list;
    queue<Creature> temp_creature_list;
    queue<Food *> food_list;

    for (int i = 0; i < num_food; i++) {
        double food_type_numeric = food_chance(eng);
        int food_size = int(floor(food_size_range(eng)));
        int start_x = int(floor(location_start_xrange(eng)));
        int start_y = int(floor(location_start_yrange(eng)));
        int min_size = int(floor(floor(food_size*0.8)));

        // int nutrients_left;
        // int min_size;
        // int nibble_size;
        // int x;
        // int y;
        // int size;
        
        int size_given = 1;
        double energy_returned_percentage;

        // Under the assumption most to least common is Survival, beneficial, nutritious
        if (food_type_numeric < chance_of_survival_food) { 
            // Survival found
            size_given = 1;
            energy_returned_percentage = 0.25;
            
        } else if (food_type_numeric < chance_of_survival_food + chance_of_beneficial_food) {
            // Beneficial found
            size_given = 2;
            energy_returned_percentage = 0.50;

        } else {
            // Nutritious found
            size_given = 4;
            energy_returned_percentage = 1;

        }
        
        Food *new_food_pointer = new Food{food_size, min_size, size_given, start_x, start_y, food_size, energy_returned_percentage};
        food_list.push(new_food_pointer);


       }

    for (int i = 0; i< num_creat; i++) {
        double size = size_range(eng);
        double splitting_factor = splitting_range(eng);
        double speed = speed_range(eng);
        
        // To reward larger creatures, we will proivde them with more relative energy. 
        double proportial_energy_cap = (size/avg_size)*max_energy;
        std::uniform_real_distribution<double> energy_range(min_energy, proportial_energy_cap);
        double energy = energy_range(eng);

        int start_x = int(floor(location_start_xrange(eng)));
        int start_y = int(floor(location_start_yrange(eng)));

        Food *closest_food_ptr = find_closest_food(food_list, start_x, start_y);

        Creature new_creature{start_x, start_y, speed, size, 1, splitting_factor, energy, energy, closest_food_ptr};
        new_creature.lock_on_to_target();
        creature_list.push(new_creature);

        temp_creature_list.push(new_creature);
    }


    // test_scripts(food_list, creature_list);
    cout << "\n\n\n\n\n MAIN SCRIPT ACTIVATED: ";
    if (food_debug) {food_data_full(food_list);}
    
    queue<Creature> *creature_list_pointer = &creature_list;
    try {
        main_script(food_list, creature_list_pointer);
    } catch (invalid_argument a) {
        if (creature_debug) {animal_data_condensed(creature_list);}
    }
    if (condensed_out) {
        animal_data_condensed(*creature_list_pointer);
    }
    
    get_all_averages(creature_list_pointer);

}


int main() {

    if (user_input_loop) {
        while (true) {
            int user_num_creatures;
            int user_num_food;
            int user_avg_size;

            cout << "NUMBER OF CREATURES (-1 to exit)...";
            cin >> user_num_creatures;

            if (user_num_creatures == -1) {
                break;
            }

            cout << "NUMBER OF FOOD...";
            cin >> user_num_food;

            cout << "AVERAGE SIZE...";
            cin >> user_avg_size;

            run_animal_house(user_num_creatures, user_num_food, user_avg_size);

        }
    } else {
        run_animal_house(number_of_creatures, number_of_food_per_round, average_size);
    }
    


    return 1;

}

