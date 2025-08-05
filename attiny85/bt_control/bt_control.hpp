#ifndef __BT_CONTROL_H__
#define __BT_CONTROL_H__

#define MAIN_BUTTON      3
//#define RESET_BUTTON     1
#define LED_0            2
#define LED_1            4
//#define RX_PIN           2
//#define TX_PIN           3
// Times determined experimentally
#define TIME_POWER       4000
#define TIME_PAIR_ON     200
#define TIME_PAIR_OFF    100
#define TIME_PAIR_SAMPLE 500
#define LED_VALID_SAMPLE 150

typedef enum BtState {
  OFF,
  POWER_ON,
  POWER_OFF,
  ACTIVE,
  PAIR,
  PAIR_WAIT,
  PAIR_PUSH_1,
  PAIR_PUSH_2,
  PAIR_PUSH_3,
  PAIRING
} btState_t;

class BtControl {
  private:
    int _lock;
    int _timer;
    int _callback_missed;
    int _led0_acc;
    int _led1_acc;
    btState_t _module_state;
    void _acquire_lock();
    void _release_lock();
    void _set_timer(int time);
  public:
    void _timer_callback();
    BtControl();
    void update();
    void write_io(int output, int value);
    int  read_io(int input);
    void power_on();
    void power_off();
    void pair();
    btState_t get_status();
};

#endif __BT_CONTROL_H__