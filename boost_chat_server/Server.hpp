#ifndef BOOST_CHAT_SERVER_HPP
#define BOOST_CHAT_SERVER_HPP
#include "GUI.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/thread.hpp>
#include <string>
#include <list>

class Server
{
public:
    explicit Server(unsigned short port);
    ~Server();
    void Listen();
    void Run();
private:
    static const unsigned int m_size_buffer = 1024;
    struct client
    {
        boost::asio::ip::tcp::socket m_socket;
        std::string m_name;
        char m_buffer[m_size_buffer];
        client* next;
        explicit client(boost::asio::io_service* io_service) : m_socket{*io_service} {}
    };
    void AcceptingConnections();
    //handline methods
    void AcceptHandline(client* current, const boost::system::error_code& error);
    void ReadHandline(client* current, const boost::system::error_code& error,
                      size_t bytes_transferred);
    void WriteHandline(client* current, const boost::system::error_code& error);
    //work with list
    void DeleteOneClient(client* del);

    GUI* m_gui;
    boost::asio::io_service* m_ioservice;
    boost::asio::ip::tcp::acceptor* m_acceptor;
    boost::thread* m_ioservice_thread;
    client* m_clients = nullptr;
    unsigned int m_active_connections = 0;
};

#endif //BOOST_CHAT_SERVER_HPP
