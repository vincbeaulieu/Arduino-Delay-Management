# Arduino - Delay Management
This short tutorial will demonstrate how to efficiently implement a delay(), without having to compromise the response time and performances of your arduino system. 

## Things to consider:  
- The millis() function counts the number of interrupts generated when Timer_0 overflows [[1]].  
- The built-in delay() function use millis() to completely halt the program for a given time [[2]].  
- The millis() return type is "unsigned long" [[3]].

[1]: https://forum.arduino.cc/t/problem-enabling-timer0-impacts-general-digital-io-toggle-rate-arduino-uno/676869/4  
[2]: https://forum.arduino.cc/t/which-timer-used-on-mega-for-delay-and-delaymicroseconds/420641/2
[3]: https://learn.sparkfun.com/tutorials/data-types-in-arduino/all  

## Important to understand about millis()
The millis() function is a function that keeps track of the current_time. Whenever you assign millis() to a variable, your variable will hold a snapshot of the value that millis() **<ins>had</ins>** when it was assigned to your variable. This means that a variable can only hold the previous_time, never the current_time, because millis() is the current_time ***[see Notes under this code]***. If you want to be using the name current_time instead of millis(), you can use the following declaration at the top of your code:

```C++
#define current_time millis()
```
***[Notes]:*** There are some exceptions to this. Sometime you may have to "freeze" the current_time to perform some computations that are time-sensitive. And you do not want the current_time value to change while you are using it. Otherwise, it may lead to undesirable behaviour. Therefore, you can "freeze" the current_time by taking a snapshot of it (capturing it) into a variable. Many programmers will often call this new variable the *"current_time"*, which can be misleading for some people, thus it is preferable to name such variable *"captured_time"* instead.

## The Problem: CPU Being Busy at Waiting (Sequential Delay)
The delay() or wait() function acts both by halting the program entirely, and nothing else can be executed in the meantime. Using such delays are \*<ins>**BAD PRACTICES**</ins>\* as they drastically reduce the capabilities and performances of a system. Below is an implementation of a wait() function using millis().  
  
```C++
// Avoid using wait() or delay() when possible
void delay(unsigned long delay){
    unsigned long previous_time = millis(); // Save the current time
    while(millis() < previous_time + delay); // Wait until time has elapsed
}
```
  
When the above code is executed, we save the *current_time* given by *millis()*, into the variable named *previous_time*. Then, a while loop is executed as long as the condition *current_time < previous_time + delay* is true, emulating a "wait" in your program. This type of waiting is referred as ***"Busy Waiting"***. As the name implies, you are using a CPU resource to wait, which isn't a great use of the resource. On rare occasions, a wait () or delay() function can be used to mitigate a Race Condition, or when doing isolated program testing.

## The Solution: Delay Traking and Management Routine

You may have certain tasks that you may want to execute at given intervals such as:
- Take a measurement from the ultrasonic sensors after 100 ms (take measurement, wait 100ms, take another measurement, ...)
- Deactivate the fans for 50 ms
- Print results every 2000 ms

However, if you are implementing these tasks using a delay() or wait() function, each task will cumulate the delays of the others. Resulting in 2150 ms of response time in your system. Which is terribly slow. Instead, periodically check if the desired delay has been met or exceeded for a given task, and execute when it is true. Else, go to the next task and repeat.

### Global Structure Holding the Previous Times of each Functions
```C++
// Previous Times Tracking Array
volatile struct {
    unsigned long hello = millis();
    unsigned long world = millis();
    unsigned long print = millis();
    // ...              <------- add more lines as needed
} PREVIOUS_TIMES;
```
  
### Busy Waiting Approach (DON'T DO THAT!):  
```C++
// AVOID! This code takes 250ms of CPU resources to do nothing!
int hello(double stuff){
    //DO NOT USE THIS FUNCTION! (BAD PRACTICE!)
    delay(250); // wait 250ms
    
    // Does something useful
    printf("%.2f\n", stuff);
    
    // Return something if needed
    return 0;
}
```
***[Notes]:*** This approach is called *"Busy Waiting"*, where the code takes 250ms of CPU resources to do nothing.
  
### Sporadic Approach:  
```C++
string world(double stuff){
    // Points/Refers to the previous time assigned to print (PREVIOUS_TIMES.print)
    volatile unsigned long *previous_time = &PREVIOUS_TIMES.print;
    
    // Set your delay
    unsigned long delay = 1000;
    
    // Check if the delay has been reached
    if(millis() >= *previous_time + delay){
        
        // Place your code here (Critical section)
        printf("\t%.2f\n", stuff);
        
        // Update PREVIOUS_TIMES.print to current_time
        *previous_time = millis();
    }
    
    // Return something if needed
    return "More stuff";
}
```
***[Notes]:*** This approach is sporadic, but recurring. The task will first execute, then release the CPU resource, then wait 2000ms before "asking" for the CPU again. After the delay of 2000 ms has elapsed, then the task is *ready* again to be re-executed.

### Periodic Approach:  
```C++
void print(double stuff){
    // Points/Refers to the previous time assigned to world (PREVIOUS_TIMES.world)
    volatile unsigned long *previous_time = &PREVIOUS_TIMES.world;
    
    // Set your period
    unsigned long period = 2000; // ms
    
    // Initiallize the next time period this task should be executed
    unsigned long next_time = *previous_time + period;
    
    // Check if the next period has begun
    if(millis() >= next_time){
        
        // Place your code here (Critical section)
        printf("\t\t%.2f\n", stuff);
        
        // Update PREVIOUS_TIMES.world by adding the period
        *previous_time = next_time;
    }
    
    // Return something if needed
    return;
}
```
***[Notes]:*** This approach is periodic. It gives your task a periodic nature by telling that this task *should* execute every 1000 ms (soft-deadline).

### Main loop():
```C++
void loop() {
    hello(...);
    world(...);
    print(...);
}
``` 

## Limitations:
The delay management algorithm presented in this documentation is an overly simplified and inspired version of a *mostly static* scheduling algorithm (scheduler) [[4]]. It is intended for single processor only. It does not have a "ready queue", but rather a list of tasks to be executed when ready.  Moreover, the algorithm presented in this documentation only handles soft-deadlines, it is not designed for hard-deadlines (no priority queue).

[4]: https://stackoverflow.com/questions/40069587/advantages-and-disadvantages-with-static-and-dynamic-scheduling

## References:  
[1\] https://forum.arduino.cc/t/problem-enabling-timer0-impacts-general-digital-io-toggle-rate-arduino-uno/676869/4  
[2\] https://forum.arduino.cc/t/which-timer-used-on-mega-for-delay-and-delaymicroseconds/420641/2  
[3\] https://learn.sparkfun.com/tutorials/data-types-in-arduino/all  
[4\] https://stackoverflow.com/questions/40069587/advantages-and-disadvantages-with-static-and-dynamic-scheduling  
  
## Additional Resources:
[A\] https://www.industrialshields.com/blog/arduino-industrial-1/post/industrial-arduino-millis-vs-delay-248#:~:text=In%20a%20complex%20program%2C%20this,possible%20to%20do%20it%20simultaneously.  
[B\] https://www.baeldung.com/cs/os-busy-waiting
