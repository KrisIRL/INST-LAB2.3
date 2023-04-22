#include "mbed.h"
#include "C12832.h" // Include the C12832 library for the LCD display

C12832 lcd(p5, p7, p6, p8, p11); // Initialize the LCD display

InterruptIn joystickcenter(p14); // Initialize the InterruptIn object for the joystick button
InterruptIn button(p9); // Initialize the InterruptIn object for the external button
DigitalOut led(LED1); // Initialize the DigitalOut object for the LED
DigitalOut flash(LED4); // Initialize the DigitalOut object for the flashing LED

volatile int var = 0; // Declare a volatile integer variable to be set by the interrupt service routine

void flip() {
    led = !led; // Toggle the state of the LED
    var = 1; // Set the variable to 1 to indicate that the button has been pressed
}

int main() {
    joystickcenter.rise(&flip); // Attach the flip() function to the rising edge of the joystick button
    button.mode(PullUp); // Set the mode of the external button to PullUp to avoid using an external pullup resistor
    button.rise(&flip); // Attach the flip() function to the rising edge of the external button

    while(1) { // Infinite loop
        flash = !flash; // Toggle the state of the flashing LED
        wait(0.25); // Wait for a quarter of a second
        if(var) { // Check if the variable has been set by the interrupt service routine
            lcd.cls(); // Clear the LCD screen
            lcd.printf("Button pressed!"); // Print a message to the LCD screen
            var = 0; // Reset the variable to 0
        }
    }
}
