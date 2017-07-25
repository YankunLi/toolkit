/*
 *
 *Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#include "Dog.h"

Dog::Dog() {}

Dog::Dog(string name, int age): Animal(name, age) {}

Dog::~Dog() {}

void Dog::run() {
    cout << "I am a Dog, I will running" << endl;
}
