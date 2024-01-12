#include "heat_resistor.h"
#include "motors.h"
#include "tds.h"
#include <SoftwareSerial.h>
SoftwareSerial BTserial(/*RX = */17, /*TX = */16);
DualMotor engine(41,43,45,47);
TdsSensor tds1(A0);
void setup(){
    engine.enable_EN(39,49);
}
void loop(){
    engine.move();

}


/*Second Commit*/
/*Third Commit*/
/*Forth commit*/
/*Fifth commit*/
/*Sixth commit*/
/*Seventh commit*/
/*Eighth commit*/