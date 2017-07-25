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

    v = new Dog("mikle", 23);

    boost::get<Dog>(v).run();
}
