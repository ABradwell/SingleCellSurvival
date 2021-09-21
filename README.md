# Simple Evolutionary Splitting program


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


## The Energy situation
    For each creature, the distance between them and the food is converted into "how much energy is needed"
    
    In this situation, energy is a relative percentage drained (larger creatures SHOULD use more to move and have to move less, however that is not taken into account in this version of the program)
    One energy unit is the equivalent to the length of the diagonal of a triangle with...

    Length ->	CREATURE SIZE
    Height ->	CREATURE SIZE

    Therefore, the length of one Energy Unit is the equivalent to SQRT( SIZE^2 + SIZE^2 )

    Creating a hitbox around the creature (a square with length of creature size and a height of creature size),
    A diagonal is calculated between the bottom-left & top right corners.
    The length of this diagonal is the equivilent of one energy unit.

    All distaces between a creature and a food object are converted into these units, and each step drains the appropriate energy from the creature.
    If the creature runs out of energy without reaching a food obejct, it will die.