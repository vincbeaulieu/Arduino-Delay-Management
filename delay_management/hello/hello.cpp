//
//  hello.cpp
//  test
//
//  Created by Vincent Beaulieu on 2022-11-26.
//

#include "hello.h"

// AVOID! This code takes 250ms of CPU resources to do nothing!
int hello(double stuff){
    //DO NOT USE THIS FUNCTION! (BAD PRACTICE!)
    delay(250); // wait 250ms
    
    // Does something useful
    printf("%.2f\n", stuff);
    
    // Do or Return something if needed
    return 0;
}
