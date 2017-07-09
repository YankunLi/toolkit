#ifndef _H_CONFIG
#define _H_CONFIG

struct config_t
{
    char name[20];
    int old;

config_t();
~config_t();

void set_name(const char* name);
void set_old(const int old);
char * get_name() const;
int get_old() const;
};

#endif
