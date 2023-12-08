#include "two_numbers.h"

int main () {
  int a = 6;
  int b = 5;

  TwoNumbers num(a, b);

  cout << "The numbers are: " << a << " and " << b << endl;
  cout << "Addition result: " << num.addNumbers() << endl;
  cout << "Multiplication result: " << num.multiplyNumbers() << endl;

  return 0;
}