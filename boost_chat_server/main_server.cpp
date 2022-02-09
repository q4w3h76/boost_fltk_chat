#include "Server.hpp"
#include <iostream>

int main()
{
    Server* server;
    try
    {
        server = new Server{7500};
        server->Listen();
        server->Run();
        delete server;
    }
    catch (boost::system::system_error const& error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
        delete server;
        return -1;
    }

    return 0;
}
