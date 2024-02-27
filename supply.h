#ifndef SUPPLY_AS1203
#define SUPPLY_AS1203 1
#include "motors.h"
class Supply: public Motor{
    private:
        int supply_delay = 1000;
        unsigned long supply_interval = -1;
        int nowtime = millis();
        int nowtime_s = millis();
        bool supplying = false;
    public:
        Supply(const int p1, const int p2){
            init(p1, p2);
        }
        void start_service(){
            motor_turn();
            if(supplying){
                set_speed(1);
                if(millis() - nowtime_s >= supply_delay){
                    supplying = false;
                    stop();
                }
            }else{
                if(millis() - nowtime >= supply_interval && supply_interval != -1){
                    supply(true);
                }
            }
        }
        void set_supply_delay(int dt){
            supply_delay = dt;
            return;
        }
        void set_supply_interval(int it){
            supply_interval = it;
            return;
        }
        void supply(bool reset = false){
            nowtime_s = millis();
            supplying = true;
            if(reset){
                nowtime = millis();
            }
        }

};
#endif