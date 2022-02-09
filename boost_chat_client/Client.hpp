#ifndef BOOST_FLTK_CLIENT_CLIENT_HPP
#define BOOST_FLTK_CLIENT_CLIENT_HPP
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

class Client {
public:
    Client(const std::string& name, const std::string& ip = "127.0.0.1");
    ~Client();
    void SendMessage(const char* message);
    boost::asio::ip::tcp::socket* GetSocket();
private:
    const unsigned short m_port = 7500;
    boost::asio::io_service* m_ioservice;
    boost::asio::ip::tcp::endpoint* m_endpoint;
    boost::asio::ip::tcp::socket* m_socket;
};


#endif //BOOST_FLTK_CLIENT_CLIENT_HPP
