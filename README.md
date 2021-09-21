# SingleCellSurvival# Simple Evolutionary Splitting program


## Overview
The included program aims to create a simulation of very VERY simple evolutionary tendencies. 
A random selection of creatures (represented by some colored circle), which will then begin to compete for food. 
These creatures will begin with some random selection of abiltiies. AS they split, these qualtiies will spread to their decendants.

Along side the program is an information window describing which generations were created, survived, and which were culled. 


## Creatures
The creatures have a simple goal: gain enough SIZE to be able to split into two. 
Moving takes up ENERGY
Creatures must move to the FOOD to gain SIZE & regain ENERGY
Larger creatures require less ENERGY to move the same distance as a smaller creature
Larger creatures require more FOOD than smaller creatures to SPLIT (Thus why they are larger)

Creatures will be spawned with some combination of the following parameters
||      Splitting factor        [4, 50]
||      Speed                   [1, 100]
||      Size                    [0.5, 100]
//      Energy                  [0, 1000]           (Not implemented)


## Food Sources
Food will be spawned according to three types. 
||      Survival     (s_chance %)        +1 Size        1/4 refill energy
||      Beneficial   (b_chance %)        +2 Size        1/2 refill energy
//      Nutrutious   (n_chance %)        +4 Size        full refill energy


## Energy & Size
|| All creatures can be either fast or slow
|| A large and small creature can cover the same space in the same time
||      The larger creature will require less energy to do this than the small creature
|| 
||      Therefore there needs to be some correlation between size (S), speed(V), and energy used(E)
||      Let speed be defined as how any body lengths a creature can travel per move
||      Let D be defined as the distance between the food and the creature
||      
||      Energy drain = Speed to travel (in the terms of body lengths)
||      IE      E = V/S 
//



## Doubling // Splitting
|| When a creatures reaches its SPlitting Factor Size, it will divide itself into the next generation.
|| THe first draft will maintain the exact genetics of the creature's predecessor
|| Future drafts will allow for minor mutations
//



Patch One
## The Energy situation
    A massive part of this program is that the creatures must die.
    As such, their energy must tick down, only restored when they eat. 
    This way, even if the creture NEVER splits, it WILL survive. 

    Each creature is moving on a realtive grid, where one grid-spot forward
    represents one energy taken. One slot forward is the body size of the creature. 

    Therefore a creature that is half the size of the ap will only need 2 energy to reach the other side. 
    To prevent this the splitting facotr's max range must be lowered

    A C