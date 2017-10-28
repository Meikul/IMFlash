/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include "main.h"
/*
-OUTPUT-
1 R mobile goal getter
2 R lift
3 L lift
4 R mid drive
5 R outer drive
6 L outer drive
7 L mid drive
8 cone getter
9 cone getter
10 L mobile goal getter
-INPUT-
1 L encoder
2 L encoder
9 L pot
10 R pot
11 R encoder
12 R encoder
-CONTROLLER-
Tank drive
Lift Top left for up
Bottom left for down
Top right to intake
Bottom right to outtake
Right pad up to mobile goalgetter out
Right pad down to mobile goalgetter in
*/
void driveSet(int, int);
void liftSet(int);
void mogoSet(int);
void intakeSet(int);
void operatorControl() {
 while (1) {

  // Drive
  int L = joystickGetAnalog(1,3);
  int R = joystickGetAnalog(1,2);
  lcdPrint(uart1, 1, "R: %d, L: %d", R, L);
  driveSet(L, -R);

  // Lift
  unsigned int pDead = 100;
  unsigned int pot = analogRead(9);
  int lift = (joystickGetDigital(1, 6, 2) - joystickGetDigital(1, 6, 1))*127;
  if((lift == 0) && (pot > pDead)){
   // p control here
   liftSet(40);
  }
  else liftSet(lift);

  //Getter
  int mogo = (joystickGetDigital(1, 7, 2) - joystickGetDigital(1, 7, 1))*127;
  mogoSet(mogo);

  //Intake
  int intake = (joystickGetDigital(1, 5, 2) - joystickGetDigital(1, 5, 1))*127;
  intakeSet(intake);
  delay(20);
 }
}
void driveSet(int left, int right){
 motorSet(6,left);
 motorSet(7,-left);
 motorSet(4,right);
 motorSet(5,-right);
}
void liftSet(int pwr){
 motorSet(2, -pwr);
 motorSet(3, pwr);
}
void mogoSet(int pwr){
 motorSet(1, -pwr);
 motorSet(10, pwr);
}
void intakeSet(int pwr){
 motorSet(8, pwr);
 motorSet(9, -pwr);
}
