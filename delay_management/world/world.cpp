//
//  world.cpp
//
//  Created by Vincent Beaulieu on 2022-11-26.
//

#include "world.h"

string world(double stuff){
    // Points/Refers to the previous time assigned to "world" (PREVIOUS_TIMES.world)
    volatile unsigned long *previous_time = &PREVIOUS_TIMES.world;
    
    // Set your delay
    unsigned long delay = 1000;
    
    // Check if the delay has been reached
    if(millis() >= *previous_time + delay){
        
        // Place your code here
        printf("\t %.2f\n", stuff);
        
        // Update PREVIOUS_TIMES.world to current_time
        *previous_time = millis();
    }
    
    // Do or Return something if needed
    return "More stuff";
}

