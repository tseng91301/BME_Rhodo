#include "heat_resistor.h"
#include "motors.h"
#include "tds.h"
#include "timer.h"
#include "uarttransfer.h"
#include "bt_contorl.h"
#include "supply.h"
#include "phMeter.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
DualMotor engine(41,43,45,47);
TdsSensor tds1(A0);
Timer timer;
// BTcontorl contorl1(/*TX = */18, /*RX = */19);
BTcontorl2 contorl1(115200);
// HRmod waterTemp(A1);
Supply feed_machine(28, 30);
Supply chemical_machine(32, 34);
PhMeter phmeter(A2);
DS18B20 heat_sen(A3);
void setup(){
    Serial.begin(115200);
    // engine.enable_EN(39, 49);
    // feed_machine.enable_EN(26);
    feed_machine.set_supply_interval(2*60*60*1000);
    // chemical_machine.enable_EN(36);
    timer.add(transfer_data,/*delayTime = */ 200);
    engine.stop();
}
void loop(){
    phmeter.start_service();
    feed_machine.start_service();
    chemical_machine.start_service();
    heat_sen.start_service();
    timer.execute();
    engine.move();
    if(contorl1.receive()){
        handle_command(contorl1.getstr());
    }
    delay(1);
}
void transfer_data(){
    DynamicJsonDocument values(200);
    values["tds"] = tds1.value();
    values["temp"] = heat_sen.value();
    values["ph"] = phmeter.val();

    String values_o;
    serializeJson(values, values_o);
    contorl1.send(values_o);
    // Serial.println(values_o);
}
void handle_command(String inp){
    // Serial.println(inp);
    if(inp=="LF"){
        engine.set_left_speed(1);
    }
    if(inp=="LS"){
        engine.set_left_speed(0);
    }
    if(inp=="LB"){
        engine.set_left_speed(-1);
    }
    if(inp=="RF"){
        engine.set_right_speed(1);
    }
    if(inp=="RS"){
        engine.set_right_speed(0);
    }
    if(inp=="RB"){
        engine.set_right_speed(-1);
    }
    if(inp=="FeedOn"){
        feed_machine.set_speed(1);
    }
    if(inp=="FeedOff"){
        feed_machine.set_speed(0);
    }
    if(inp=="ChemOn"){
        chemical_machine.set_speed(1);
    }
    if(inp=="ChemOff"){
        chemical_machine.set_speed(0);
    }
    if(inp.indexOf("Spd")!=-1){
        String s;
        int l = inp.length();
        for(int a=3;a<l;a++){
            s += inp[a];
        }
        double s2 = (double)(s.toInt())/(double)100;
        engine.set_speed(s2);
    }
}

/*13th commit*/