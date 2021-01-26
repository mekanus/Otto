#include <Servo.h>
#include "Otto.h"
#include "US.h"
#include "Oscillator.h"
#include <SoftwareSerial.h>

double Ordre;

Otto robot_otto;
SoftwareSerial bt_serial(6, 7);
double math_random_int(int a, int b) {
  if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
  return (double)random(a, b + 1);
}

void RepOrdre() {
  if ((bt_serial.available() > 0)) {
    Ordre = bt_serial.parseFloat();
    Serial.println(Ordre);

  }
}

void MouOtto() {
  if ((Ordre == 1)) {
    robot_otto.walk(1, 1000, 1);
    robot_otto.putMouth(10, true);

  } else if ((Ordre == 2)) {
    robot_otto.turn(1, 1000, 1);
    robot_otto.putMouth(15, true);
  } else if ((Ordre == 3)) {
    robot_otto.turn(1, 1000, -1);
    robot_otto.putMouth(15, true);
  } else if ((Ordre == 4)) {
    robot_otto.walk(1, 1000, -1);
    robot_otto.putMouth(29, true);
  } else if ((Ordre == 5)) {
    robot_otto.home();
    robot_otto.putMouth(16, true);
  }
  else {
    robot_otto.home();

  }
}

void ObstacleDetectat() {
  robot_otto.home();
  for (int count = 0; count < 2; count++) {
    robot_otto.sing(S_confused);
    robot_otto.playGesture(OttoConfused);
  }
  robot_otto.bend(1, 1000, 1);
  robot_otto.bend(1, 1000, -1);
  if ((math_random_int(0, 1) == 0)) {
    for (int count = 0; count < 2; count++) {
      robot_otto.turn(1, 1000, -1);
    }

  } else {
    for (int count = 0; count < 2; count++) {
      robot_otto.turn(1, 1000, 1);
    }

  }
  Ordre = 1;
}

void setup()
{
  robot_otto.init(2, 3, 4, 5, false, A6, 13, 8, 9);
  robot_otto.setTrims((-20), (-10), (-18), 5);
  bt_serial.begin(9600);

  Serial.begin(9600);

  randomSeed(analogRead(0));
  robot_otto.sing(S_connection);
  robot_otto.home();
  robot_otto.playGesture(OttoHappy);


}


void loop()
{

  if (((robot_otto.getDistance() < 10) && (Ordre != 5))) {

    ObstacleDetectat();


  }
  RepOrdre();
  MouOtto();

}
