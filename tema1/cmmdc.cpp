#include "calculator.h"

int Calculator::cmmdc(int a, int b){
    if(a<b){
        int aux = a;
        a=b;
        b=aux;
    }   

    while(b!=0){
        int aux = b;
        b = a%b;
        a=aux;
    }
    return a;
}