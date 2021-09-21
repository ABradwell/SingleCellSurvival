#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

int myglobalint;
int number_of_creatures = 40;
int number_of_food_per_round = 20;
int number_of_iterations = 200000;

double chance_of_survival_food = 0.35;
double chance_of_beneficial_food = 0.50;
double change_of_nutrutious_food = 0.15;

double min_size = 2;
double max_start_size = 15; // Overall max size of 100 as determined by 2* 

double max_size = 100;
double min_splitting_factor = 7;
double max_splitting_factor = max_size/2;

double average_size = 60;

double min_speed = 0.9;
double max_speed = 1.4;

double min_energy = 0;
double max_energy = 1000;


double map_width = 1600;
double map_height = 900;
double map_vertical_proportion = map_height/map_width;


bool food_debug = false;
bool creature_debug = false;
bool splitting_debug = false;
bool condensed_out = true;

bool user_input_loop = true;

#endif