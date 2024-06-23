#include <iostream>

#include "KIApplication.hpp"

int main(int, char**)
{
    KIApplication& app = *KIApplication::instance();
    app.init();
    if (!app.run())
        KIApplication::destroyInstance();
    return 0;
}
