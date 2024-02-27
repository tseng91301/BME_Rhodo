#ifndef TDS_SENSOR_DF4328
#define TDS_SENSOR_DF4328 1

double pow2(double, int);
class TdsSensor{
    private:
        int recv_pin;
        int data_filter = 10;
    public:
        TdsSensor(const int rec){
            recv_pin = rec;
            pinMode(rec,INPUT);
            return;
        }
        double value(){
            double t1=0.0;
            for(int a=0;a<data_filter;a++){
                int t2=analogRead(recv_pin);
                if(!t2){
                    t1+=0.001;
                }else{
                    t1+=(double)t2;
                }
                delay(1);
            }
            t1/=data_filter;
            t1=t1*5.0/1024.0;
            // double tdsValue=(133.42/pow2(t1,3) - 255.86*pow2(t1,2) + 857.39*t1)*0.5; //Convert voltage value to TDS value
            double tdsValue=(133.42*t1 - 255.86*pow(t1, 2) + 857.39*t1)*0.5; //Convert voltage value to TDS value
            return tdsValue+0.0001;
        }
};
double pow2(double inp, int n){
    double out = 1.0;
    for(int a=0;a<n;a++){
        out*=inp;
    }
    return out;
}
#endif