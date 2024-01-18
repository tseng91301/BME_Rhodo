#include "heat_resistor.h"
#include "motors.h"
#include "tds.h"
#include "timer.h"
#include "uarttransfer.h"
#include "bt_contorl.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
DualMotor engine(41,43,45,47);
TdsSensor tds1(A0);
Timer generate_detector_data;
BTcontorl contorl1(/*TX = */16, /*RX = */17);
void setup(){
    Serial.begin(9600);
    engine.enable_EN(39,49);
    generate_detector_data.add(transfer_data,/*delayTime = */ 200);
}
void loop(){
    generate_detector_data.execute();
    engine.move();
    if(contorl1.receive()){
        Serial.println(contorl1.getstr());
    }
}
void transfer_data(){
    DynamicJsonDocument values(200);
    values["tds"] = tds1.value();
    values["temp"] = 25.0;
    values["ph"] = 7.0;

    String values_o;
    serializeJson(values, values_o);
    contorl1.send(values_o);
}

/*13th commit*/