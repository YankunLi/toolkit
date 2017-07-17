/*
 * Author: Yankun Li
 *
 */
#include <iostream>

#include "Object.h"

using namespace std;

Object::Object() {
    cout << "Default construction" << endl;
}

Object::Object(Object& obj) {
    cout << "Copy constructor" << endl;
}

Object::~Object() {
    cout << "Destructor" << endl;
}

