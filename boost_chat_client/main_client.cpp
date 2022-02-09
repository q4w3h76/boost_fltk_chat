#include "Window.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
		std::cout << "Enter your name and IP address of the server" << std::endl;
        return -1;
    }
    Window* window;
	try
	{
		window = new Window(argv[1], argv[2]);
		Fl::run();
		delete window;
	}
	catch(boost::system::system_error const& error)
	{
		std::cerr << "Exception: " << error.what() << std::endl;
		delete window;
		return -1;
	}

	return 0;
}
