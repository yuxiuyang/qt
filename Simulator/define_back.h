#ifndef DEFINE_H
#define DEFINE_H
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <iostream>
#include <string.h>
using namespace std;
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

#endif // DEFINE_H
