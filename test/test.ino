#include "phMeter.h"
#include "timer.h"
PhMeter phmeter(A2);
Timer ph_getval;
void setup(){
    Serial.begin(115200);
    ph_getval.add(print_ph_val, 500);
    ph_getval.add(led_on, 400, 0);
    ph_getval.add(led_off, 400, 200);
    pinMode(LED_BUILTIN, OUTPUT);
}
void loop(){
    phmeter.start_service();
    ph_getval.execute();
}
void print_ph_val(){
    Serial.print("pH value: ");
    Serial.println(phmeter.val());
}
void led_on(){
    Serial.println("led_on");
    digitalWrite(LED_BUILTIN, HIGH);
}
void led_off(){
    Serial.println("led_off");
    digitalWrite(LED_BUILTIN, LOW);
}
