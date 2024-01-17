#ifndef UARTTRANSFER_WE4325
#define UARTTRANSFER_WE4325 1

#define baud_rate 115200
int data_to_motor(char inp){
    int out;
    switch (inp)
    {
        case 'F':
            out=0;
            break;
        case 'B':
            out=1;
            break;
        case 'L':
            out=2;
            break;
        case 'R':
            out=3;
            break;
        case 'I':
            out=5;
            break;
        case 'G':
            out=4;
            break;
        case 'S':
            out=6;
        default:
            break;
    }
    return out;
}
void uartsend(String inp){
    int l=inp.length();
    for(int a=0;a<l;a++){
        if(inp[a]!='\0'){
            Serial.write((char)inp[a]);
        }
    }
    Serial.write('\n');
}
/*if (command == "F") goAhead();
else if (command == "B") goBack();
else if (command == "L") goLeft();
else if (command == "R") goRight();
else if (command == "I") goAheadRight();
else if (command == "G") goAheadLeft();
else if (command == "S") stopRobot();*/

#endif