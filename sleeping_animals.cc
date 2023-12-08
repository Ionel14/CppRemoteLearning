#include "animal.h"

void MakeAnimalsSleep() {
  Animal** animals = new Animal*[5];

  for (int i = 0; i < 5; i++) {
    animals[i] = new Animal();
    animals[i]->Sleep();
    delete animals[i];
  }
  
  delete[] animals;
}
