#ifndef MOTORS_GH2842
#define MOTORS_GH2842 1
#include<math.h>

class Motor{
    protected:
        int pin1;
        int pin2;
        int ENpin;
        bool haveEN = false;

        double pid = 1;
        double speed = 0;
        int analog_max = 1023;
    public:
        void init(const int p1, const int p2){
            pin1 = p1;
            pin2 = p2;
            pinMode(p1, OUTPUT);
            pinMode(p2, OUTPUT);
            return;
        }
        void enable_EN(const int enp){
            ENpin = enp;
            pinMode(enp, OUTPUT);
            haveEN = true;
            return;
        }
        void motor_turn(){
            static int s_before = -1;
            int s_in = analog_max*speed*pid;
            int s2;
            if(haveEN){
                analogWrite(ENpin, abs(s_in));
                s2 = analog_max;
            }else{
                s2 = abs(s_in);
            }
            if(s_in > 0){
                analogWrite(pin1, s2);
                analogWrite(pin2, 0);
            }else{
                analogWrite(pin1, 0);
                analogWrite(pin2, s2);
            }
        }
        void set_analog_max(int in){
            analog_max = in;
            return;
        }
        void set_speed(double inp){
            speed = inp;
            return;
        }
        void set_pid(double in){
            pid = in;
            return;
        }
        void stop(){
            speed = 0;
            analogWrite(pin1, 0);
            analogWrite(pin2, 0);

            if(haveEN){
                analogWrite(ENpin, 0);
            }
            return;
        }
};
class DualMotor{
    protected:
        double speed = 0.5;
        double leftspeed = 0;
        double rightspeed = 0;

        Motor mL;
        Motor mR;

        int fb = 1;
    public:
        DualMotor(const int l1,const int l2,const int r1,const int r2){
            mL.init(l1, l2);
            mR.init(r1, r2);
        }
        void enable_EN(const int enl,const int enr){
            mL.enable_EN(enl);
            mR.enable_EN(enr);
        }
        void move(){
            mL.set_speed(leftspeed*speed);
            mR.set_speed(rightspeed*speed);
            // Serial.print("L");
            mL.motor_turn();
            // Serial.print("R");
            mR.motor_turn();
        }
        void turn_deg(double deg_in){//0 is forward, clockwise
            int fb2 = fb;
            if(fb2 == 0){
                fb2 = 1;
            }
            if(deg_in<=180&&deg_in>=0){ //right
                leftspeed = fb2*1;
                rightspeed = fb2*sin(deg_in+90);
            }else if(deg_in<=0&&deg_in>=-180){ //left
                leftspeed = fb2*sin(deg_in+90);
                rightspeed = fb2*1;
            }
            return;
        }
        void set_analog_max(int inp){
            mL.set_analog_max(inp);
            mR.set_analog_max(inp);
            return;
        }
        void set_speed(double inp){
            speed = inp;
        }
        void set_left_speed(double inp){
            leftspeed = inp;
        }
        void set_right_speed(double inp){
            rightspeed = inp;
        }
        void set_pid(double inp){
            if(abs(inp-1.0)<=0.0001){
                mL.set_pid(1);
                mR.set_pid(1);
            }else if(inp>1.0){
                double pid_after = double(1.0/inp);
                mL.set_pid(pid_after);
                mR.set_pid(1);
            }else{
                mL.set_pid(1);
                mR.set_pid(inp);
            }
            return;
        }
        void stop(){
            mL.stop();
            mR.stop();
            leftspeed = 0;
            rightspeed= 0;
            fb = 0;
            return;
        }
        void back(){
            leftspeed = -1;
            rightspeed = -1;
            fb = -1;
            return;
        }
        void forward(){
            leftspeed = 1;
            rightspeed = 1;
            fb = 1;
            return;
        }
        int get_FB_state(){
            return fb;
        }
};
#endif