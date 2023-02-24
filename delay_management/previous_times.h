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
// Secrets of Arduino PWM
// https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
//
//
// PID control
// https://www.arrow.com/en/research-and-events/articles/pid-controller-basics-and-tutorial-pid-implementation-in-arduino  
//
// How to interpret IMU Sensor data  
// https://www.allaboutcircuits.com/technical-articles/how-to-interpret-IMU-sensor-data-dead-reckoning-rotation-matrix-creation/  
//

