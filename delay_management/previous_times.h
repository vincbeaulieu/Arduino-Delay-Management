//
//  previous_times.hpp
//  test
//
//  Created by Vincent Beaulieu on 2023-02-14.
//

#ifndef previous_times_h
#define previous_times_h

// Library declarations
#include <iostream>
using namespace std;

// Standard Arduino Function Declarations
inline unsigned long millis(){
    return clock()/((double)CLOCKS_PER_SEC/1000);
} // Already included in Arduino's Libraries

// Standard Arduino Function Declarations
inline void delay(unsigned long delay){
    unsigned long previous_time = millis();
    while(millis() < previous_time + delay);
} // Already included in Arduino's Libraries

// Previous Times Tracking Array
volatile struct {
    unsigned long hello = millis();
    unsigned long world = millis();
    unsigned long print = millis();
    // ...              <------- add more lines as needed
} PREVIOUS_TIMES;

#endif /* previous_times_h */


// Additional Resources:
//
//
// Volatile Struct Usage:
// https://stackoverflow.com/questions/246127/why-is-volatile-needed-in-c/
//
//
// US sensor without delay
// https://arduino.stackexchange.com/questions/36875/hc-sr04-distance-measuring-without-delay
//
//


