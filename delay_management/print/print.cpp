//
//  print.cpp
//  test
//
//  Created by Vincent Beaulieu on 2022-11-26.
//

#include "print.h"

void print(double stuff){
    // Points/Refers to the previous time assigned to world (PREVIOUS_TIMES.world)
    volatile unsigned long *previous_time = &PREVIOUS_TIMES.world;

    // Set your period
    unsigned long period = 2000; // ms

    // Initiallize the next time period this task should be executed
    unsigned long next_time = *previous_time + period;

    // Check if the next period has begun
    if(millis() >= next_time){
        
        // Place your code here
        printf("\t\t  %.2f\n", stuff);
        
        // Update PREVIOUS_TIMES.world by adding the period
        *previous_time = next_time;
    }

    // Do or Return something if needed
    return;
}


