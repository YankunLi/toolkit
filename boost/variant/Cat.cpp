/*
 *
 * Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#include "Cat.h"

Cat::Cat() {}

Cat::Cat(string name, int age): Animal(name, age) {}

Cat::~Cat() {}

void Cat::run() {
    cout << "I am a cat, i will jump" << endl;
}
