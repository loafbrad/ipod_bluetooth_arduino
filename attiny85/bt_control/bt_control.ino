// ATtiny85 implementation
// Removed debug prints to save memory
#include <SoftwareSerial.h>
#include "bt_control.hpp"

//Serial ipodserial();
BtControl airfly_state;

void setup() {
  // NOTE: This value will need to be adjusted depending on what oscillator speed is set to.
  // Multiply by 2 if running at 8MHz internal oscillator.
  Serial.begin(9600);

  // Connecting the LED pin outputs on the Airfly Pro to these two input pins
  //pinMode(LED_0, INPUT_PULLUP);
 // pinMode(LED_1, INPUT_PULLUP);
  DDRB  |= 0b00001000;
  DDRB  &= 0b11101011;
  PORTB |= 0b00011100;

  // Configure internal timer
  // Section 12.3 of ATtiny25/45/85 [DATASHEET] Rev. 2586Q–AVR–08/2013
  cli();
  // Divide counter1 by 256
  TCCR1  = 0b00001001;
  // Use system clock 8Mhz for Timer1
  PLLCSR = 0b00000000;
  // OCIE1A enable
  TIMSK |= 0b01000000;
  // NOTE: Adjust timer here based on target clock frequency to trigger interrupt at desired interval.
  // ~1ms
  OCR1A = 32;
  sei();
}

// Interrupt service routine for when timer triggers. Run Bluetooth Control callback.
ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  airfly_state._timer_callback();
}

void loop() {
  //Serial.println("test");
  if (Serial.available() > 0) {
    // Read serial input from the iPod
    String fromipod = Serial.readStringUntil('\n');
    fromipod.trim();

    // Perform action based on 
    if (fromipod.equals("btc_poweron")) {
      //ipodserial.println("Powering on!");
      airfly_state.power_on();
    } else if (fromipod.equals("btc_poweroff")) {
      //ipodserial.println("Powering off!");
      airfly_state.power_off();
    } else if (fromipod.equals("btc_pair")) {
      //ipodserial.println("Paring!");
      airfly_state.pair();
    } else if (fromipod.equals("btc_status")) {
      Serial.println(airfly_state.get_status());
    }  
  }
}

