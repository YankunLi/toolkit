#include <iostream>
#include <cstring>
using namespace std;

#include "config.h"

config_t::config_t()
{}

config_t::~config_t()
{}

void config_t::set_name(const char *name)
{
    strcpy(this->name, name);
}

void config_t::set_old(const int old)
{
    this->old = old;
}

char *config_t::get_name() const
{
    return (char *) name;
}

int config_t::get_old() const
{
    return old;
}

