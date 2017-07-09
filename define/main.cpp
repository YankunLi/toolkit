#include <iostream>
#include "config.h"

using namespace std;


#define OPTION(name, type, value) \
    do { \
        cout << value << " who are you? " #name " my name is " #name " " << b_##type << endl;\
    } while(0);

int main(int argc, char *argv[])
{
    int b_int333 = 9;
#include "define.h"
#undef OPTION
    config_t stuff;
    char name[] = "liyankun";
    stuff.set_name((char *)name);
    stuff.set_old(25);
    cout << "name : " <<(char *) (stuff.get_name()) << "\tage : " << stuff.get_old() << endl;

    return 0;

}
