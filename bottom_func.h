#ifndef SELFMAKE_BOTTOM_FUNC
#define SELFMAKE_BOTTOM_FUNC 1

int charnum(String strin,char search_w){
    //Serial.println("charnum");
    int num=0;
    int inl=strlen(strin.c_str());
    for(int a=0;a<inl;a++){
        //Serial.println(strin[a]);
        if(strin[a]==search_w){
            num++;
        }
    }
    return(num);
}
void fillarray(String *instrarr,String instr,char divide_c){
    //Serial.println("fillarray");
    int len_instr=strlen(instr.c_str());
    int tmp1=0;
    int tmp2=0;
    for(int a=0;a<len_instr;a++){
        //Serial.println(instr[a]);
        if(instr[a]==divide_c){
            //Serial.print("divide_strarr");
            //Serial.println(instrarr[tmp1]);
            //Serial.println("arr_next");
            tmp2=0;
            tmp1++;
        }else{
            instrarr[tmp1]+=instr[a];
        }
    }
}
bool range(int in,int m_in,int M_in=-1){
    if(M_in==-1){
        return(in>=m_in);
    }
    return(in<M_in&&in>=m_in);
}
String trimstr(String strin,int start_l,int end_l){
    String strout="";
    for(int a=start_l;a<end_l;a++){
        strout+=strin[a];
    }
    return(strout);
}

#endif