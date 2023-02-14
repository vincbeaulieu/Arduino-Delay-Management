//
//  main.cpp
//  test
//
//  Created by Vincent Beaulieu on 2022-11-25.
//

// Headers dependencies
#include "header.h"

// Prototypes
double get_time(clock_t);
void tasks_routine();

// Global variables
clock_t ti, tf;

int main(int argc, const char * argv[]) {
    cout << "Process Routine :\n" << "hello\n" << "\t world\n" << "\t\t  print\n";
    cout << "____|____|____\n";
    
    // Initialize time for benchmarking
    ti = clock();
    
    // Test function
    int time_out = 10; // seconds
    while(time_out > get_time(clock())) tasks_routine();
    
    // End of benchmark
    tf = clock();
    double benchmark = get_time(tf);
    cout << "\nBenchmark: " << benchmark << " seconds" << endl;
}

double get_time(clock_t t){
    return (t - ti)/(double)CLOCKS_PER_SEC;
}

// Tasks routine
void tasks_routine() {
    hello(get_time(clock()));
    world(get_time(clock()));
    print(get_time(clock()));
}


