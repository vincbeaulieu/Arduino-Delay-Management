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
The delay() function acts like a wait in your program, and it is sequential. It halt the program entirely, and nothing else can be executed in the mean time. Using such delay's are bad practice has they drastically reduce the capabilities and performances of a system. Below I've provided an alternative to the delay() function which directly use millis(), ***but try to avoid using it, or using delay().***
```C++
// Avoid using sequential delay when possible
void wait(unsigned long delay){
    unsigned long previous_time = millis(); // Save the current time
    while(millis() < previous_time + delay); // Wait until time has elapsed
}
```
When the above code is executed, we save the *current_time* given by *millis()*, into the variable named *previous_time*. Then, a while loop is execute as long as the condition *current_time < previous_time + delay* is true, emulating a "wait" in your program. These are often useful when your program is running into problems such as a Race Condition.

## Important to understand about millis()
The millis() function is a function that keep tracks of the current_time. Whenever you assign millis() to a variable, your variable will hold a snapshot of the value that millis() **<ins>had</ins>** when it was assigned to your variable. This means that a variable can only hold the previous_time, never the current_time, because millis() is the current_time. If you want to be using the name current_time instead of millis(), use the following declaration at the top of your code:

```C++
#define current_time millis()
```
## The Solution: Delay Traking and Management Routine
