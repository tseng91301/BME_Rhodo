#ifndef TIMER_FDS34323
#define TIMER_FDS34323 1
typedef void (*TimerFunctionPointer)(void);
class Timer{
    private: 
        struct FunctionDetail{
            TimerFunctionPointer func;
            int offset;
            int DelayTime;
            int TmpTime;
            int execute_num = 0;
        };
        int storeFunc_num = 0;
        FunctionDetail *storeFunc = (FunctionDetail*)malloc(storeFunc_num*sizeof(FunctionDetail));
        
    public: 
        void add(TimerFunctionPointer f_in, int delayTime = 1000, int offset = 0){
            storeFunc_num++;
            storeFunc = (FunctionDetail*)realloc(storeFunc, storeFunc_num*sizeof(FunctionDetail));
            FunctionDetail added;
            added.func = f_in;
            added.DelayTime = delayTime;
            added.TmpTime = millis();
            added.offset = offset;
            storeFunc[storeFunc_num-1] = added;
        }
        void execute(){
            for(int a=0;a<storeFunc_num;a++){
                int nowtime = millis();
                if(nowtime - storeFunc[a].TmpTime >= storeFunc[a].offset && storeFunc[a].execute_num==0){
                    storeFunc[a].TmpTime = nowtime;
                    storeFunc[a].func();
                    storeFunc[a].execute_num++;
                }
                if((nowtime - storeFunc[a].TmpTime >= storeFunc[a].DelayTime) && storeFunc[a].execute_num){
                    storeFunc[a].TmpTime = nowtime;
                    storeFunc[a].func();
                    storeFunc[a].execute_num++;
                }
            }
        }
        ~Timer(){
            free(storeFunc);
        }
};
#endif