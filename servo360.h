#ifndef SERVO360_FDSH32819
#define SERVO360_FDSH32819 1
#include<Servo.h>
class Servo360: public Servo{
    protected:
        int servoPin;
        int roundtime = 550;

        int write_spd = 90;
        int nowtime = millis();
        int turn_delay_time = 0;

        int pause_delay = 30;
        bool pause = false;
    public:
        virtual void start_service(){
            write(write_spd);
            if(millis() - nowtime >= turn_delay_time){
                turn_delay_time = 0;
                write_spd = 90;
            }
        }
        void set_round_time(int inp){
            roundtime = inp;
            return;
        }
        void turn30(int dir){
            int turn_time = roundtime * (double(abs(30)) / double(360));
            if(dir){
                write_spd = 180;
            }else{
                write_spd = 90;
            }
            turn_delay_time = turn_time;
        }
        void turndeg(int deg){
            bool r_c = (deg >= 0);
            turn_delay_time = roundtime * (double(abs(deg)) / double(360));
            if(r_c){
                write_spd = 180;
            }else{
                write_spd = 0;
            }
            return;
        }

};
#endif