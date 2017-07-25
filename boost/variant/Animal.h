/*
 *
 *Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#ifndef _H_ANIMAL_
#define _H_ANIMAL_

#include <string>

class Animal {
    private:
        string a_name;
        string a_description;
        int a_age;

    public:
        Animal();
        Animal(string name, int age);
        Animal(string name, int age, string desc);
        virtual ~Animal();

        virtual void run() = 0;
};

#endif
