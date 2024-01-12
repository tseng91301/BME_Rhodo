#ifndef HEAT_RESISTOR_FJ3842
#define HEAT_RESISTOR_FJ3842 1
class HRmod{
    private:
        int recv_pin;
        int BETA = 3950;
        int max_val = 1023;
    public:
        HRmod(const int rpin,int mv = -1){
            recv_pin = rpin;
            pinMode(rpin,INPUT);
            if(mv!=-1){
                set_max_val(mv);
            }
        }
        void set_beta(int inp){
            BETA = inp;
            return;
        }
        void set_max_val(int inp){
            max_val = inp;
            return;
        }
        double value(){
            int analogValue = analogRead(recv_pin);
            analogValue = map(analogValue, 0, max_val, 0, 1023);
            double celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
            return celsius;
        }
};
#endif