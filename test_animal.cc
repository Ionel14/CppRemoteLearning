#include "animal.h"

int main() {
  Animal* animal = new Animal();

  animal->MakeSound();
  animal->Sleep();

  delete animal;
  
  MakeAnimalsSleep();
  
  return 0;
}
