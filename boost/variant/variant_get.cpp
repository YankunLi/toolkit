/*
 *
 * Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#include <boost/variant.hpp>
#include <string>
#include <iostream>

using namespace std;

#include "Dog.h"
#include "Cat.h"

int main(int argc, char *argv[])
{
    typedef boost::variant<Dog, Cat> Var_t;

    Var_t v;

    Dog *d = new Dog("mikle", 23);
    v = *d;

    Cat *c = boost::get<Cat>(&v);
    if (!c) {
        cout << "is not a cat" << endl;
    }

    try {
        boost::get<Dog>(v).run();
    } catch (boost::bad_get &) {
        cout << "bad_get" << endl;
    }

    return 0;
}
