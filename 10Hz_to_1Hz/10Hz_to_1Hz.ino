

// 1 Hz signal pin
int oneHz = 11;

// interrupt pin 10 Hz
int interruptPin = 2;

// the flag for the 1 Hz signal
volatile boolean flag = false;

// half period
unsigned long halfPeriod = 5000000UL; // 5000mS = 1/2 Hz



void setup() {
  // put your setup code here, to run once:

  // define the pinModes
  pinMode(oneHz, OUTPUT);
  pinMode(interruptPin, INPUT); // ??? OR INPUT_PULLUP ???

  // ISR - interrupt service routine 
  attachInterrupt(digitalPinToInterrupt(interruptPin), foo, RISING);

}



void loop() {
  // put your main code here, to run repeatedly:
  while (flag){ // avoid  loop() jitter

    // time critical - turn off interrupts
    noInterrupts();
  
    PINB = PINB | 0b00001000; // x-x-13-12-11-10-9-8 on Uno,
                                             // toggle output by writing 1 to input register
    delayMicroseconds(halfPeriod);

    // set flag back to false
    flag = false;
    
    // not time critical
    interrupts(); 
  }

}

// if in the ISR, change the flag to true
void foo() {

  flag = true; 
  
}
