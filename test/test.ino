#include "phMeter.h"
PhMeter phmeter(A2);
void setup(){
    Serial.begin(115200);
}
void loop(){
    Serial.println(phmeter.val());
}
