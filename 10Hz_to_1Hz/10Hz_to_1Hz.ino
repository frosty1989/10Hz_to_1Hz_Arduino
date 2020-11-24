// include library for proper use of 
#include <util/delay.h>

// 1 Hz signal pin
int oneHz = 11;

// interrupt pin 10 Hz
int interruptPin = 2;

// duration of interrupt
volatile unsigned long Duration = 0;

// the flag for the 1 Hz signal
volatile boolean flag = false;

// interrupt counter
volatile int count = 0;

void setup() {

  // Set up serial
  //Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  
  // put your setup code here, to run once:

  // define the pinModes
  pinMode(oneHz, OUTPUT);
  pinMode(interruptPin, INPUT); // ??? OR INPUT_PULLUP ???

  // ISR - interrupt service routine 
  attachInterrupt(digitalPinToInterrupt(interruptPin), foo, RISING);

  digitalWrite (11, LOW); // known starting level
}

void loop() {
  // put your main code here, to run repeatedly:
  if (flag){ // avoid  loop() jitter

    // time critical - turn off interrupts
    //noInterrupts();

    // toggle output by writing 1 to input register
    PINB = PINB | 0b00001000; // x-x-13-12-11-10-9-8 on Uno,


    _delay_ms(1000);
    //delay(1000);

    // replace the delay with a 

    PINB = PINB | 0b00000000; // x-x-13-12-11-10-9-8 on Uno,


    // set flag back to false
    flag = false;

    // print interrupt duration
    // Serial.println(Duration, DEC);
    
    // not time critical
    //interrupts(); 
  }

}

// if in the ISR, change the flag to true
void foo() {

  unsigned long then = micros();
  
  count++;

  if (count % 10 == 0) {


   // set the flag to true
   flag = true;  

   // reset the counter
   count = 0;
   
  }

  else {
    
    return;  
    
  }

  //unsigned long now = micros();
  //Duration = now - then;
  

  
}
