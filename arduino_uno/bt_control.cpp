#ifndef __BT_CONTROL_CPP__
#define __BT_CONTROL_CPP__
#include "bt_control.hpp"
#include "Arduino.h"
#include <string.h>

void __debug_print(String a) {
  Serial.println(a);
}

BtControl::BtControl() {
  this->_lock = 0;
  this->_timer = 0;
  this->_callback_missed = 0;
  this->_led0_acc = 0;
  this->_led1_acc = 0;
  this->_module_state = OFF;
};

void BtControl::update() {
  if (this->_callback_missed) {
    this->_timer_callback();
    this->_callback_missed = 0;
  }
}

btState_t BtControl::get_status(){
  return this->_module_state;
};

void BtControl::_acquire_lock(){
  this->_lock = 1;
};

void BtControl::_release_lock(){
  this->_lock = 0;
};

// TODO: Not sure if "ms" is an accurate measure for time in this setup...
void BtControl::_set_timer(int time_ms) {
  this->_timer = time_ms;
};

void BtControl::write_io(int output, int value) {
  if (value == 1) {
    PORTB = 0x00;
  } else {
    PORTB = 0xFF;
  }
};

int BtControl::read_io(int input) {
  return digitalRead(input);
};

void BtControl::_timer_callback() {
  // Run this function whenever microcontroller timer triggers.
  // Run every <TODO> ms.
  // This function will preempt any other function which modifies state or I/O behavior.
  if (this->_lock) {
    this->_callback_missed = 1;
    return;
  }
  if (_timer) _timer--;

  switch (this->_module_state) {
    case OFF:
    break;
    case POWER_ON:
      if (!_timer) {
        this->_module_state = ACTIVE;
        this->write_io(MAIN_BUTTON, 0);
        __debug_print("Moving to state active");
      }
      break;
    case POWER_OFF:
      if (!_timer) {
        this->_module_state = OFF;
        this->write_io(MAIN_BUTTON, 0);
      }
      break;
    case PAIR:
      // Write to I/O twice in quick succession
      this->_module_state = PAIR_PUSH_1;
      this->_timer = TIME_PAIR_ON;
      this->write_io(MAIN_BUTTON, 1);
      __debug_print("Pair!");
      break;
    case PAIR_PUSH_1:
      // Write to I/O twice in quick succession
      if (!_timer) {
        this->_module_state = PAIR_PUSH_2;
        this->_timer = TIME_PAIR_OFF;
        this->write_io(MAIN_BUTTON, 0);
        __debug_print("Moving to state push 2");
      }
      break;
    case PAIR_PUSH_2:
      // Write to I/O twice in quick succession
      if (!_timer) {
        this->_module_state = PAIR_PUSH_3;
        this->_timer = TIME_PAIR_ON;
        this->write_io(MAIN_BUTTON, 1);
        __debug_print("Moving to state push 3");
      }
      break;
    case PAIR_PUSH_3:
      // Write to I/O twice in quick succession
      if (!_timer) {
        this->_module_state = PAIR_WAIT;
        this->write_io(MAIN_BUTTON, 0);
        this->_timer = TIME_PAIR_OFF*2;
        __debug_print("Moving to state push wait");
      }
      break;
    case PAIR_WAIT:
      // Write to I/O twice in quick succession
      if (!_timer) {
        this->_module_state = PAIRING;
        this->_timer = TIME_PAIR_SAMPLE*3;
        __debug_print("Waiting for pair");
      }
      break;
    case PAIRING:
      // Sample LED outputs
      // The purpose of this function is to sample the LED outputs from the Airfly Pro
      // to determine if the Airfly Pro is still in it's pairing state.
      this->_led0_acc += (PIND & (1 << LED_0)) ? 1 : 0;
      this->_led1_acc += (PIND & (1 << LED_1)) ? 1 : 0;
      if (!_timer) {
        if (this->_led0_acc < LED_VALID_SAMPLE || this->_led1_acc < LED_VALID_SAMPLE) {
          this->_module_state = ACTIVE;
          __debug_print("Sampling success");
          Serial.println(this->_led0_acc);
          Serial.println(this->_led1_acc);
        }
        this->_led0_acc = 0;
        this->_led1_acc = 0;
        this->_timer = TIME_PAIR_SAMPLE;
      }
      break;
    };
};

void BtControl::power_on() {
  // Move to POWER_ON state only if we are idle.
  // Do nothing else if we are in any other state because
  // the module is already powered on.
  this->_acquire_lock();
  if (this->_module_state == OFF) {
    this->_module_state = POWER_ON;
    this->write_io(MAIN_BUTTON, 1);
    this->_set_timer(TIME_POWER);
  }
  this->_release_lock();
};

void BtControl::power_off() {
  // Move to POWER_ON state only if we are idle.
  // Do nothing else if we are in any other state because
  // the module is already powered on.
  this->_acquire_lock();
  if (this->_module_state == ACTIVE || this->_module_state == PAIRING) {
    this->_module_state = POWER_OFF;
    this->write_io(MAIN_BUTTON, 1);
    this->_set_timer(TIME_POWER);
  }
  this->_release_lock();
};

void BtControl::pair() {
  // "Double press" to pair
  this->_acquire_lock();
  if (this->_module_state == ACTIVE) {
    this->_module_state = PAIR;
  }
  this->_release_lock();
};

#endif