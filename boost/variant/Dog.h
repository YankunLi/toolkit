/*
 *
 * Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#ifndef _H_DOG_
#define _H_DOG_

#include <iostream>

using namespace std;

#include "Animal.h"

class Dog: public Animal {
    public:
        Dog();
        Dog(string name, int age);
        virtual ~Dog();

        virtual void run();
};

#endif
