#include "heat_resistor.h"
#include "motors.h"
#include "tds.h"
#include "timer.h"
#include "uarttransfer.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial BTserial(/*RX = */17, /*TX = */16);
DualMotor engine(41,43,45,47);
TdsSensor tds1(A0);
Timer generate_detector_data;
void setup(){
    engine.enable_EN(39,49);
    generate_detector_data.add(transfer_data,/*delayTime = */ 200);
}
void loop(){
    engine.move();
}
void transfer_data(){
    DynamicJsonDocument values(200);
    values["tds"] = tds1.value();
    values["temp"] = 25.0;
    values["ph"] = 7.0;

    String values_o;
    serializeJson(values, values_o);
    uartsend(values_o);
}

/*13th commit*/