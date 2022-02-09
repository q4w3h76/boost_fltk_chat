#include "Server.hpp"
#include <iostream>

int main()
{
    Server server(7500);
    server.Listen();
    server.Run();

    return Fl::run();
}
