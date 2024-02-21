#ifndef PH_METER_DS3245
#define PH_METER_DS3245 1
class PhMeter{
    private:
        int sensorPin;
        double offset = 0.00;
        int sample_num = 40;
        int now_sample_num = 0;
        double pHvalue = 0.0;
        int *val_arr = nullptr;

        int get_val_delay = 20;
        int get_val_nowtime = millis();
    public:
        PhMeter(const int pin){
            // pinMode(pin, INPUT);
            val_arr = new int[sample_num];
            sensorPin = pin;
            return;
        }
        ~PhMeter(){
            delete[] val_arr;
        }
        void start_service();
        double val(){
            return pHvalue;
        }
        double avergearray(int*, int);
};

void PhMeter::start_service(){
    if(millis()-get_val_nowtime >= get_val_delay){
        // Record value
        val_arr[now_sample_num++] = analogRead(sensorPin);
        if(now_sample_num==sample_num){
            double vol = avergearray(val_arr, sample_num) * 5.0 / 1024.0;
            pHvalue =  3.5 * vol + offset;
            now_sample_num = 0;
        }
        get_val_nowtime = millis();
    }
}

double PhMeter::avergearray(int* arr, int number){
    /*Need reference of this section of code (function)*/
    int i;
    int max,min;
    double avg;
    long amount=0;
    if(number<=0){
        Serial.println("Error number for the array to averaging!/n");
        return 0;
    }
    if(number<5){   //less than 5, calculated directly statistics
        for(i=0;i<number;i++){
            amount+=arr[i];
        }
        avg = amount/number;
        return avg;
    }
    else{
        if(arr[0]<arr[1]){
            min = arr[0];max=arr[1];
        }
        else{
            min=arr[1];max=arr[0];
        }
        for(i=2;i<number;i++){
            if(arr[i]<min){
                amount+=min;        //arr<min
                min=arr[i];
            }
            else{
                if(arr[i]>max){
                    amount+=max;    //arr>max
                    max=arr[i];
                }
                else{
                    amount+=arr[i]; //min<=arr<=max
                }
            }//if
        }//for
        avg = (double)amount/(number-2);
    }//if
    return avg;
}
#endif