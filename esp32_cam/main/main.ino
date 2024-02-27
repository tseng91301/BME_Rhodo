/*
Demo with Arduino Car (an Android app)

the Serial read input:
Forward: 70 'F'
Backward: 71 'B'
Left: 83 'L'
Right: 82 'R'
Left Front: 81 'G'
Right Front: 69 'I'
Left Back: 90 'Z'
Right Back: 67 'C'
Stop: 83 'S'

Front light (switch) 77 'M'
Back light (switch) 78 'N'

Mode X: 88 'X'
Mode Y: 89 'Y'
 */
#include <ArduinoJson.h>
#include <BluetoothSerial.h> 
#include "ble.h"
BluetoothSerial SerialBT; 

void setup() {
    Serial.begin(115200);
    SerialBT.begin(BLUETOOTH_NAME); //name the bluetooth and initialize
    // Serial.println("begin!");
}

void loop() {
    if (SerialBT.available()) {
        char dat=SerialBT.read();
        Serial.write(dat);
        if(dat == '}'){
            Serial.write('\n');
        }
        delay(1);
        // if(dat>='A'&&dat<='Z'){
        //     Serial.write(dat);
        // }
    }
    while(Serial.available()){
        String json_in="";
        char t=Serial.read();
        while(t!='\n'){
            json_in+=t;
            t=Serial.read();
            delay(3);
        }
        SerialBT.println(json_in);
        /*DynamicJsonDocument values(200);
        DeserializationError error = deserializeJson(values, json_in);
        if(!error){
            double t1=values["tds"];
            SerialBT.println(int(t1*100));
            Serial.println(t1);
        }*/
    }
}
