#include <iostream>
#include "calculator.h"

int main(){
    Calculator calculator;

    int result1 = calculator.cmmdc(26, 65);
    int result2 = calculator.max_digit(215934);

    std::cout<<"CMMDC between 26 and 65 is: "<<result1<<std::endl;
    std::cout<<"The maximal digit of the number 215934 is: "<<result2<<std::endl;

    return 0;
}