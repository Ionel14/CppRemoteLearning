#include "calculator.h"

int Calculator::max_digit(int a){
    int maxi = 0;
    while(a!=0){
        if(a%10>maxi){
            maxi = a%10;
        }
        a=a/10;
    }
    return maxi;
}