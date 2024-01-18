#ifndef MOTORS_GH2842
#define MOTORS_GH2842 1
#include<math.h>

class DualMotor{
    protected:
        int left1pin;
        int left2pin;
        int leftENpin;
        int right1pin;
        int right2pin;
        int rightENpin;
        bool haveEN = false;

        double leftpid = 1;
        double rightpid = 1;

        double speed = 0.5;
        double leftspeed = 0;
        double rightspeed = 0;
        int analog_max = 1023;
    public:
        DualMotor(const int l1,const int l2,const int r1,const int r2){
            pinMode(l1,OUTPUT);
            pinMode(l2,OUTPUT);
            pinMode(r1,OUTPUT);
            pinMode(r2,OUTPUT);
            left1pin = l1;
            left2pin = l2;
            right1pin = r1;
            right2pin = r2;
        }
        void enable_EN(const int enl,const int enr){
            pinMode(enl,OUTPUT);
            pinMode(enr,OUTPUT);
            leftENpin = enl;
            rightENpin = enr;
            haveEN = true;
        }
        void motor_turn(int p1,int p2,int s_in){
            if(s_in>=0){
                analogWrite(p1,s_in);
                analogWrite(p2,0);
            }else{
                analogWrite(p1,0);
                analogWrite(p2,-s_in);
            }
        }
        void move(){
            static int lspd = -1;
            static int rspd = -1;
            int leftspd_after = analog_max*leftpid*leftspeed*speed;
            int rightspd_after = analog_max*rightpid*rightspeed*speed;

            if(leftspd_after == lspd && rightspd_after == rspd){
                return;
            }
            lspd = leftspd_after;
            rspd = rightspd_after;

            if(haveEN){
                int la2 = abs(leftspd_after);
                int ra2 = abs(rightspd_after);
                analogWrite(leftENpin,la2);
                analogWrite(rightENpin,ra2);
                motor_turn(left1pin,left2pin,(leftspd_after/la2)*analog_max);
                motor_turn(right1pin,right2pin,(rightspd_after/ra2)*analog_max);
            }else{
                motor_turn(left1pin,left2pin,leftspd_after);
                motor_turn(right1pin,right2pin,rightspd_after);
            }

        }
        void turn_deg(double deg_in){//0 is forward, clockwise
            if(deg_in<=180&&deg_in>=0){ //right
                leftspeed = 1;
                rightspeed = sin(deg_in+90);
            }else if(deg_in<=0&&deg_in>=-180){ //left
                leftspeed = sin(deg_in+90);
                rightspeed = 1;
            }
            return;
        }
        void set_analog_max(int inp){
            analog_max = inp;
            return;
        }
        void set_speed(double inp){
            speed = inp;
            return;
        }
        void set_pid(double inp){
            if(abs(inp-1.0)<=0.0001){
                leftpid = 1;
                rightpid = 1;
            }else if(inp>1.0){
                double pid_after = double(1.0/inp);
                leftpid = pid_after;
                rightpid = 1;
            }else{
                rightpid = inp;
                leftpid = 1;
            }
            return;
        }
        void stop(){
            analogWrite(left1pin,0);
            analogWrite(left2pin,0);
            analogWrite(right1pin,0);
            analogWrite(right2pin,0);
            if(haveEN){
                analogWrite(leftENpin,0);
                analogWrite(rightENpin,0);
            }
            speed = 0;
            return;
        }
        void back(){
            speed = -1*abs(speed);
        }
        void forward(){
            speed = abs(speed);
        }
};
#endif