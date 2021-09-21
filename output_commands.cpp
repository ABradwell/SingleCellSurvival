// #include "Food.h"
// #include "creature.h"


void food_data_full(queue<Food *> food_list) {

    if (food_list.size() == 0) {
        cout << "\n\nNO FOOD REMAINS...\n";
    }
    
    for (int i = 0; i< food_list.size(); i++) {
        // Food *fptr = food_list.front();
        Food *f = food_list.front();
        cout << "\n\nFOOD " << i << " INFO: \n";
        cout << "X: " << f->x << " Y: " << f->y << "\n";
        cout << "Size : " << f->size << "   || Min_Size: " << f->min_size << "\n";
        cout << "Size Given: " << f->nibble_size << "   || Energy Returned: " << f->energy_returned_percentage << "\n";
        cout << "nutrients_left: " << f->nutrients_left << "\n";
        food_list.pop();
        food_list.push(f);
    }
}

void food_data_condensed(queue<Food *> food_list) {

    if (food_list.size() == 0) {
        cout << "\n\nNO FOOD REMAINS...\n";
    }

    for (int i = 0; i< food_list.size(); i++) {
        // Food *fptr = food_list.front();
        Food *f = food_list.front();

        cout << "F @(" << f->x << ", " << f->y << ") n: "<< f->nutrients_left << " |  s: "<< f->size << "";

        food_list.pop();
        food_list.push(f);
    }
}

void animal_data_full(queue<Creature> creature_list) {

    if (creature_list.size() == 0) {
        cout << "\n\nNO CREATURE REMAINS...\n";
    }

    for (int i = 1; i<= creature_list.size(); i++) {
        Creature c = creature_list.front();
        // Food targ = c.get_target();
        cout << "\n\nCREATURE " << i << " INFO: \n";
        cout << "X: " << c.x << " Y: " << c.y << "\n";
        cout << "Size: " << c.size << "  || Splitting Factor: " << c.splitting_factor << "\n";
        cout << "Generation: " << c.generation << "\n";
        cout << "Current Energy: " << c.cur_energy << "  || Max Energy " << c.max_energy << "  || Speed " << c.speed << "\n";
        cout << "DistDiag @ " << c.distdiag << ", {distx: " << c.distx << ", disty: " << c.disty << "}\n";
        cout << "Hunting food pointer @ " << c.target->x<< ", " << c.target->y << "(" <<c.target->nutrients_left << " remaining) \n";
        
        creature_list.pop();
        creature_list.push(c);
    }
}

void animal_data_condensed(queue<Creature> creature_list) {

    if (creature_list.size() == 0) {
        cout << "\n\nNO CREATURE REMAINS...\n";
    }

    for (int i = 1; i<= creature_list.size(); i++) {
        Creature c = creature_list.front();

        cout << "C" << i << " @(" << c.x << ", " << c.y << ") \tsplt: "<< c.splitting_factor << " \t|  size: "<< c.size << " \t|  spd: "<< c.speed << " \t|  gen: "<< c.generation << "\n";

        creature_list.pop();
        creature_list.push(c);
    }
}



void get_all_averages(queue<Creature> *creature_list_pointer){


    double average_gen = 0;
    double lowest_gen = 1000000;
    double highest_gen = -1;

    double average_speed = 0;
    double lowest_speed = 1000000;
    double highest_speed = -1;

    double average_size = 0;
    double lowest_size = 1000000;
    double highest_size = -1;

    double average_splitting_factor = 0;
    double lowest_splitting_factor = 1000000;
    double highest_spltting_factor = -1;

    if (creature_list_pointer->size() == 0) {
        cout << "\n\nNO CREATURE REMAINS...\n";
    }

    queue<Creature> creature_list = *creature_list_pointer;
    for (int i = 1; i<= creature_list.size(); i++) {
        Creature c = creature_list.front();

        double speed = c.speed;
        double size = c.size;
        double splitting_factor = c.splitting_factor;
        double gen = c.generation;

        lowest_gen = std::min(lowest_gen, gen);
        lowest_size = std::min(lowest_size, size);
        lowest_splitting_factor = std::min(lowest_splitting_factor, splitting_factor);
        lowest_speed = std::min(lowest_speed, speed);

        highest_gen = std::max(highest_gen, gen);
        highest_size = std::max(highest_size, size);
        highest_spltting_factor = std::max(highest_spltting_factor, splitting_factor);
        highest_speed = std::max(highest_speed, speed);


        average_size = average_size + size;
        average_gen = average_gen + gen;
        average_speed = average_speed + speed;
        average_splitting_factor = average_splitting_factor + splitting_factor;


        creature_list.pop();
        creature_list.push(c);
    }

    average_size = average_size/ creature_list.size();
    average_gen = average_gen/ creature_list.size();
    average_speed = average_speed/ creature_list.size();
    average_splitting_factor = average_splitting_factor/ creature_list.size();
    


    cout << "************************************************************\n";
    cout << "\t\tLow\t\tAverage\t\tHigh\n";
    cout << "Speed:\t\t" << lowest_speed << "\t" << average_speed << "\t\t" << highest_speed << "\n";
    cout << "Generation:\t" << lowest_gen << "\t\t" << average_gen << "\t\t" << highest_gen << "\n";
    cout << "Size:\t\t" << lowest_size << "\t\t" << average_size << "\t\t" << highest_size << "\n";
    cout << "Split Fact:\t" << lowest_splitting_factor << "\t\t" << average_splitting_factor << "\t\t" << highest_spltting_factor << "\n";
}