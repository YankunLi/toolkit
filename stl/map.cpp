#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *[])
{
    map<int, float> kv;
    pair<map<int, float>::iterator, bool> ret;

    ret = kv.insert(make_pair(1, 2.3));

    map<int, float>::iterator it = ret.first;
    if (ret.second)
        it->second++;

    for (map<int, float>::const_iterator i = kv.begin(); i != kv.end(); i++)
    {
        cout << "key: " << i->first << " value: " << i->second << endl;
    }

    return 0;
}
