#ifndef TIMER_FDS34323
#define TIMER_FDS34323 1
typedef void (*TimerFunctionPointer)(void);
class Timer{
    private: 
        struct FunctionDetail{
            TimerFunctionPointer func;
            int DelayTime;
            int TmpTime;
            int execute_num = 0;
        };
        FunctionDetail *storeFunc = new FunctionDetail[0];
        int storeFunc_num = 0;
    public: 
        void add(TimerFunctionPointer f_in, int delayTime = 1000){
            FunctionDetail *tmp = new FunctionDetail[storeFunc_num + 1];
            FunctionDetail added;
            added.func = f_in;
            added.DelayTime = delayTime;
            added.TmpTime = millis();
            for(int a=0;a<storeFunc_num;a++){
                tmp[a] = storeFunc[a];
            }
            tmp[storeFunc_num] = added;
            delete[] storeFunc;
            storeFunc_num++;
            storeFunc = new FunctionDetail[storeFunc_num];
            for(int a=0;a<storeFunc_num;a++){
                storeFunc[a] = tmp[a];
            }
            delete[] tmp;
        }
        void execute(){
            for(int a=0;a<storeFunc_num;a++){
                int nowtime = millis();
                if(nowtime - storeFunc[a].TmpTime >= storeFunc[a].DelayTime){
                    storeFunc[a].TmpTime = nowtime;
                    storeFunc[a].func();
                    storeFunc[a].execute_num++;
                }
            }
        }
        ~Timer(){
            delete[] storeFunc;
        }
};
#endif