/*
 * Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#include <iostream>

using namespace std;

#include "Animal.h"

Animal::Animal() {}

Animal::Animal(string name, int age)
{
    a_name = name;
    a_age = age;
}

Animal::Animal(string name, int age, string desc):
    a_name(name), a_description(desc), a_age(age)
{}

Animal::~Animal() {}
