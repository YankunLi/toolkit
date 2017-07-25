#include <boost/variant.hpp>
#include <iostream>

using namespace std;

#include "Cat.h"
#include "Dog.h"

int main(int argc, char *agrv[])
{
    typedef boost::variant<Dog, Cat> Var_t;

    Var_t v;

    v = new Cat();

    if (v.type() == typeid(Dog)) {
        boost::get<Dog>(v).run();
    } else if (v.type() == typeid(Cat)) {
        boost::get<Cat>(v).run();
    }

    return 0;
}
