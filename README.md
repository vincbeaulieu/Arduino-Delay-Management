# ENGR290 - Delay Management
Since many students are facing the same issues and struggling with code performances, I've decided to create a short tutorial on delay management.

## Things to consider:  
- The millis() function counts the number of interrupts generated when Timer_0 overflows [[1]].  
- The built-in delay() function use millis() to completely halt the program for a given time [[2]].  
- millis is "unsigned long" [[3]].

[1]: https://forum.arduino.cc/t/problem-enabling-timer0-impacts-general-digital-io-toggle-rate-arduino-uno/676869/4  
[2]: https://forum.arduino.cc/t/which-timer-used-on-mega-for-delay-and-delaymicroseconds/420641/2
[3]: https://learn.sparkfun.com/tutorials/data-types-in-arduino/all  

## The Problem: Sequential Delay
The delay() function acts like a wait in your program, and it is sequential. It halts the program entirely, and nothing else can be executed in the mean time. Using such delay's are bad practices as they drastically reduce the capabilities and performances of a system. Below I've provided an alternative to the delay() function which directly uses millis(), ***but try to avoid using it, or using delay() altogether.***
```C++
// Avoid using sequential delay when possible
void wait(unsigned long delay){
    unsigned long previous_time = millis(); // Save the current time
    while(millis() < previous_time + delay); // Wait until time has elapsed
}
```
When the above code is executed, we save the *current_time* given by *millis()*, into the variable named *previous_time*. Then, a while loop is executed as long as the condition *current_time < previous_time + delay* is true, emulating a "wait" in your program. These are often useful when your program is running into problems such as a Race Condition.

## Important to understand about millis()
The millis() function is a function that keeps track of the current_time. Whenever you assign millis() to a variable, your variable will hold a snapshot of the value that millis() **<ins>had</ins>** when it was assigned to your variable. This means that a variable can only hold the previous_time, never the current_time, because millis() is the current_time. If you want to be using the name current_time instead of millis(), use the following declaration at the top of your code:

```C++
#define current_time millis()
```
## The Solution: Delay Traking and Management Routine

You may have certain tasks that you only want to execute at a given intervals such as:
- Take a measurement from the ultrasonic sensors after 100 ms
- Deactivate the fans for 50 ms
- Print results after 2000 ms

However, if you are implement these tasks using a delay() or wait() function, each task will cumulated the delay of the other's. Resulting in 2150 ms of response time in your system. Which is terribly slow. Instead, periodically check if the desired delay has been meet or exceeded for a given task, and execute when it is true. Else, go the the next task and repeat.

### Global Pointer Array Declaration
```C++
// Previous Times Tracking Array
unsigned long * previous_times = new unsigned long []{
    millis(), // 0 : delay for hello()
    millis(), // 1 : delay for world()
    millis(), // 2 : delay for print()
    // ...       ^index               <------ Add more lines as needed
};
```
  
### Hello task:  
```C++
int hello(){
    // Assign a pointer to the index holding the previous time of this function
    unsigned long *previous_time = &previous_times[0];  // <----------- Change the index here
    
    // Set your delay
    unsigned long delay = 1;
    
    // Execute if the delay is reached
    if(millis() >= *previous_time + delay){
        
        // Place your code here
        cout << "Hello" << endl;
        
        // Update previous time to current time
        *previous_time = millis();
    }

    // Return something
    return 0;
}
```
  
### World task:  
```C++
void world(){
    // Assign a pointer to the index holding the previous time of this function
    unsigned long *previous_time = &previous_times[1];  // <----------- Change the index here
    
    // Set your delay
    unsigned long delay = 2;
    
    // Execute if the delay is reached
    if(millis() >= *previous_time + delay){
        
        // Place your code here
        cout << "\tWorld" << endl;
        
        // Update previous time to current time
        *previous_time = millis();
    }
}
```
  
### Print task:  
```C++
string print(string stuff){
    // Assign a pointer to the index holding the previous time of this function
    unsigned long *previous_time = &previous_times[2];  // <----------- Change the index here
    
    // Set your delay
    unsigned long delay = 1;
    
    // Check if the delay is reached
    if(millis() >= *previous_time + delay){
        
        // Place your code here
        cout << stuff << endl;
        
        // Update previous time to current time
        *previous_time = millis();
    }
    
    // Return something
    return "More stuff";
}
```  

### Main loop():
```C++
void loop() {
    hello();
    world();
    print();
}
``` 

Each tasks as it's own assigned previous_time and a set delay, and will only execute when the elapsed time as passed. After which, the associated previous_time is reset to the current_time holded by millis().

## References:  
[[1]] https://forum.arduino.cc/t/problem-enabling-timer0-impacts-general-digital-io-toggle-rate-arduino-uno/676869/4  
[[2]] https://forum.arduino.cc/t/which-timer-used-on-mega-for-delay-and-delaymicroseconds/420641/2  
[[3]] https://learn.sparkfun.com/tutorials/data-types-in-arduino/all  
  
