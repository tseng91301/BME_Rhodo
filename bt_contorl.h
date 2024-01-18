#ifndef BT_CONTORL_FS5438
#define BT_CONTORL_FS5438 1
#include <SoftwareSerial.h>
class BTcontorl: public SoftwareSerial{
    private:
        int txPin;
        int rxPin;
        String receive_buffer;
    public:
        BTcontorl(const int txp, const int rxp, int baudRate = 115200):
            SoftwareSerial(rxp, txp)
        {
            begin(baudRate);
            txPin = txp;
            rxPin = rxp;
        }
        bool receive(){
            if(available()){
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
#endif