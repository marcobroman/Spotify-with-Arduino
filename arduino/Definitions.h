#ifndef MY_HEADER
#define MY_HEADER

#define NONE 0
#define IR_RECEIVE_PIN 8
#define DELAY 200

#define IR_POWER 69
#define IR_VOLUP 70
#define IR_FUNCSTOP 71
#define IR_REWIND 68
#define IR_PLAY_PAUSE 64
#define IR_FASTFW 67
#define IR_DOWN 7
#define IR_VOLDOWN 21
#define IR_UP 9
#define IR_0 22
#define IR_EQ 25
#define IR_STREPT 13
#define IR_1 12
#define IR_2 24
#define IR_3 94
#define IR_4 8
#define IR_5 28
#define IR_6 90
#define IR_7 66
#define IR_8 82
#define IR_9 74

void send_button(int &button, int ir_button);
void now_playing();
void play_pause();
void read_msg();

#endif