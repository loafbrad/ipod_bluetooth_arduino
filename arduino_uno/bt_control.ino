
#include <SoftwareSerial.h>
#include "bt_control.hpp"

SoftwareSerial ipodserial(RX_PIN, TX_PIN);
BtControl airfly_state;

void setup() {
  // NOTE: This value will need to be adjusted depending on what oscillator speed is set to.
  // Multiply by 2 if running at 8MHz internal oscillator.
  ipodserial.begin(9600);

  // Connecting the LED pin outputs on the Airfly Pro to these two input pins
  pinMode(LED_0, INPUT_PULLUP);
  pinMode(LED_1, INPUT_PULLUP);
  DDRB  = 0xFF;
  PORTB = 0xFF;

  // Configure internal timer
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= 0b00000100;
  TIMSK1 |= 0b00000010;
  // NOTE: Adjust timer here based on target clock frequency to trigger interrupt at desired interval.
  // (In this particular case I say 62/2 as I reprogrammed the AVR chip to run on 8MHz internal RC oscillator vs
  // the 16MHz external clock during prototyping phase.)
  OCR1A = 62/2;
  sei();
}

// Interrupt service routine for when timer triggers. Run Bluetooth Control callback.
ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;
  airfly_state._timer_callback();
}

void loop() {
  if (ipodserial.available() > 0) {
    // Read serial input from the iPod
    String fromipod = ipodserial.readStringUntil('\n');
    fromipod.trim();

    // Perform action based on 
    if (fromipod.equals("btc_poweron")) {
      ipodserial.println("Powering on!");
      airfly_state.power_on();
    } else if (fromipod.equals("btc_poweroff")) {
      ipodserial.println("Powering off!");
      airfly_state.power_off();
    } else if (fromipod.equals("btc_pair")) {
      ipodserial.println("Paring!");
      airfly_state.pair();
    } else if (fromipod.equals("btc_status")) {
      ipodserial.println(airfly_state.get_status());
    }  
  }
}

