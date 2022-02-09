#include "Client.hpp"
#include <boost/asio/buffer.hpp>

Client::Client(const std::string& name, const std::string& ip)
    : m_ioservice{new boost::asio::io_service},
    m_endpoint{new boost::asio::ip::tcp::endpoint{boost::asio::ip::address::from_string(ip), m_port}},
    m_socket{new boost::asio::ip::tcp::socket{*m_ioservice}}
{
    m_socket->connect(*m_endpoint);
    m_socket->write_some(boost::asio::buffer(name.c_str(), name.length()));
}

Client::~Client()
{
    delete m_socket;
    delete m_endpoint;
    delete m_ioservice;
}

void Client::SendMessage(const char* message)
{
    m_socket->write_some(boost::asio::buffer(message, std::strlen(message)));
}

boost::asio::ip::tcp::socket* Client::GetSocket()
{
    return m_socket;
}