/*
 *
 *Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#ifndef _H_CAT_
#define _H_CAT_

#include <iostream>

using namespace std;

#include "Animal.h"

class Cat: public Animal {
    public:
        Cat();
        Cat(string name, int age);
        virtual ~Cat();

        virtual void run();
};

#endif
