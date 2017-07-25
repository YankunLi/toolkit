/*
 *
 *Author: Yankun Li <lioveni99@gmail.com>
 *
 */

#include <boost/variant.hpp>
#include <iostream>

using namespace std;

#include "Dog.h"
#include "Cat.h"

typedef boost::variant<Dog, Cat> Var_t;

class RunVar: public boost::static_visitor<void>
{
    public:
        void operator()(Dog& d) const {
            d.run();
        }

        void operator()(Cat& c) const {
            c.run();
        }
};

int main(int argc, char *argv[])
{
    RunVar r;
    Var_t v;

    v = new Cat("tom", 10);
    boost::apply_visitor(r, v);

    delete &boost::get<Cat>(v);

    return 0;
}
