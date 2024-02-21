#ifndef PH_METER_DS3245
#define PH_METER_DS3245 1
class PhMeter{
    private:    
        int sensorPin;
        double offset = 0.00;
        int sample_num = 40;
    public:
        PhMeter(const int pin){
            // pinMode(pin, INPUT);
            sensorPin = pin;
            return;
        }
        double get_vol(){
            int *read_arr = new int[sample_num];
            for(int a=0; a<sample_num;a++){
                read_arr[a] = analogRead(sensorPin);
                // Serial.print("Tmp value: ");
                // Serial.println(read_arr[a]);
                delay(20);
            }
            double vol = avergearray(read_arr, sample_num) * 5.0 / 1024.0;
            Serial.print("Voltage: ");
            Serial.println(vol);
            delete[] read_arr;
            return vol;
        }
        double val(){
            double pHValue = 3.5 * get_vol() + offset;
            return pHValue;
        }
        double avergearray(int*, int);
};

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