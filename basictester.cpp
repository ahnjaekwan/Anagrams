#include "Dictionary.h"
#include <string>

void f(std::string)
{
}

void g(const Dictionary& d)
{
    d.lookup("abc", f);
}

int main()
{
    Dictionary dict;
    dict.insert("abc");
    g(dict);
}
