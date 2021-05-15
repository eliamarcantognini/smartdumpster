#ifndef __CONFIG__
#define __CONFIG__

/* Led for trash type A */
#define LA_PIN 7
/* Led for trash type B */
#define LB_PIN 8
/* Led for trash type C */
#define LC_PIN 9
/* Servo's pin */
#define SERVO_PIN 12

/* Led number */
#define LED_NUM 3
/* Servo position */
#define SERVO_OPEN 180
#define SERVO_CLOSED 0
/* Deposit time */
#define DEPOSIT_TIME 5000

/* Bluetooth software serial pin */
#define BD_RX 2
#define BD_TX 3

enum TrashType {A, B, C};

#endif
