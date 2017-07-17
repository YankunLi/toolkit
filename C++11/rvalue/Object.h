/*
 *
 * Author: Yankun Li lioveni99@gmail.com
 *
 *
 */

#ifndef _RVALUE_OBJECT_H_
#define _RVALUE_OBJECT_H_

class Object {
    private:
        int value;

    public:
        Object();
        Object(Object& obj);
        //Object(Object&& obj);
        ~Object();
};

#endif
