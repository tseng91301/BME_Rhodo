#ifndef BT_CONTORL_FS5438
#define BT_CONTORL_FS5438 1
#include <SoftwareSerial.h>
void filter_str(String&);
class BTcontorl: public SoftwareSerial{
    private:
        int txPin;
        int rxPin;
        String receive_buffer;
    public:
        BTcontorl(const int txp, const int rxp, unsigned long baudRate = 115200):
            SoftwareSerial(rxp, txp)
        {
            begin(baudRate);
            txPin = txp;
            rxPin = rxp;
        }
        bool receive(){
            if(this->available()){
                Serial.println("Receiving...");
                receive_buffer = "";
                while (available()){
                    char t = read();
                    while(t != '\n'&& t != '\0'){
                        receive_buffer += t;
                        t = read();
                        delay(1);
                    }
                }
                return true;
            }else{
                return false;
            }
        }
        void send(String inp){
            println(inp);
        }
        String getstr(){
            return receive_buffer;
        }
};
class BTcontorl2{
    private:
        String receive_buffer;
    public:
        BTcontorl2(unsigned long baudRate){
            Serial1.begin(baudRate);
        }
        bool receive(){
            if(Serial1.available()){
                receive_buffer = "";
                if (Serial1.available()){
                    char t = Serial1.read();
                    while(t != '\n'&& t != '\0'){
                        if(t >= 33 && t <= 126){
                            receive_buffer += t;
                        }
                        t = Serial1.read();
                        // delay(10);
                    }
                }
                // receive_buffer = Serial1.readString();
                filter_str(receive_buffer);
                return true;
            }else{
                return false;
            }
        }
        void send(String &inp){
            Serial1.println(inp.c_str());
        }
        String getstr(){
            return receive_buffer;
        }
};
void filter_str(String &inp){
    String out;
    int l = inp.length();
    for(int a=0; a<l;a++){
        if(inp[a]>=32 && inp[a]<=126){
            out += inp[a];
        }
    }
    inp = out;
}
#endif

