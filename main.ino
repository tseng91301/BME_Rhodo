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
HRmod waterTemp(A1);
Motor feed_machine;
Motor chemical_machine;
void setup(){
    Serial.begin(9600);
    engine.enable_EN(39, 49);
    feed_machine.init(28, 30);
    feed_machine.enable_EN(26);
    chemical_machine.init(32, 34);
    chemical_machine.enable_EN(36);
    generate_detector_data.add(transfer_data,/*delayTime = */ 200);
}
void loop(){
    generate_detector_data.execute();
    engine.move();
    feed_machine.motor_turn();
    chemical_machine.motor_turn();
    if(contorl1.receive()){
        Serial.println(contorl1.getstr());
    }
}
void transfer_data(){
    DynamicJsonDocument values(200);
    values["tds"] = tds1.value();
    values["temp"] = waterTemp.value();
    values["ph"] = 7.0;

    String values_o;
    serializeJson(values, values_o);
    contorl1.send(values_o);
}
void handle_command(String inp){
    // 动态分配内存以容纳JSON对象
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, inp);
    // 检查解析是否成功
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }
    if(doc.containsKey("spd")){
        engine.set_speed(doc["spd"]);
    }
    if(doc.containsKey("fbl")){
        int fbl = doc["fbl"];
        engine.set_left_speed(fbl);
    }
    if(doc.containsKey("fbr")){
        int fbr = doc["fbr"];
        engine.set_right_speed(fbr);
    }
    if(doc.containsKey("feed")){
        int feed = doc["feed"];
        feed_machine.set_speed(feed);
    }
    if(doc.containsKey("chem")){
        int chem = doc["chem"];
        chemical_machine.set_speed(chem);
    }
}

/*13th commit*/