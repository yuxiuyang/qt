#ifndef DEFINE_H
#define DEFINE_H
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <iostream>
#include <string.h>
using namespace std;
#define MAX_DATA_BUF 120
typedef unsigned char BYTE;
typedef unsigned long int UNIT;
static BYTE charConvertToHex(char a){
        a = toupper(a);//convert Uppercase letters
        //tolower
        if(a>='0'&&a<='9'){
                return a-'0';
        }
        switch(a){
        case 'A':
                return 10;
        case 'B':
                return 11;
        case 'C':
                return 12;
        case 'D':
                return 13;
        case 'E':
                return 14;
        case 'F':
                return 15;
        default:
                return 100;
        }
        return 100;
};
static BYTE twoBYTEConverToHex(BYTE hight,BYTE low){
        assert(hight<16&&hight>=0);
        assert(low<16&&low>=0);

        //printf("hight<<4 = %d\n",hight<<4);
        return (hight<<4)|low;
}


enum LinkSource_{
    PC_Simulator_Link,//pc 模拟器 连接
    Monitor_UI_Link,//监护仪或UI 连接
    Server_Link
};
enum ClientType_{
    ECG_CLIENT,
    SPO2_CLIENT,
    CO2_CLIENT,
    NIBP_CLINET,
    IBPCO_CLIENT,
    CMD_CLIENT,//命令参数
    DISPLAY_CLIENT,
};

struct NotifyMsg_{
    LinkSource_ comeForm;
    ClientType_ type;
    bool connectState;
};
struct CmdMsg_{
    LinkSource_ comeForm;
    ClientType_ moduleType;
    int         cmd;
    void*      wparam;
    void*      lparam;
};
struct DataMsg_{
    LinkSource_ comeForm;
    ClientType_ type;
    BYTE buf[MAX_DATA_BUF];
};
enum MsgType{
    Notify_Msg,
    Cmd_Msg,
    Data_Msg,
};

struct Msg_{
    MsgType type;
    union{
        NotifyMsg_ notifyMsg;
        CmdMsg_    cmdMsg;
        DataMsg_   dataMsg;
    };
};

#endif // DEFINE_H
