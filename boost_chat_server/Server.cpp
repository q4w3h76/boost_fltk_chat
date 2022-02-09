#include "Server.hpp"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/buffer.hpp>
#include <iostream>

//public methods
Server::Server(unsigned short port)
        : m_gui(new GUI),
        m_ioservice{new boost::asio::io_service},
        m_acceptor{new boost::asio::ip::tcp::acceptor{*m_ioservice,
                                                        boost::asio::ip::tcp::endpoint{boost::asio::ip::tcp::v4(),port}}}
{
    //Set REUSEADDR
    m_acceptor->set_option(boost::asio::ip::tcp::socket::reuse_address(true));
    m_gui->Show();
}

Server::~Server()
{
    struct client* tmp;
    //deleting all item of list clients
    while(m_clients != nullptr)
    {
        tmp = m_clients;
        m_clients = m_clients->next;
        delete tmp;
    }
    delete m_gui;
    m_ioservice->stop();
    m_ioservice_thread->detach();
    delete m_ioservice_thread;
    delete m_acceptor;
    delete m_ioservice;
}

void Server::Listen()
{
    m_acceptor->listen();
    AcceptingConnections();
}

void Server::Run()
{
    m_ioservice_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, m_ioservice));
    Fl::run();
}

//private methods
void Server::AcceptingConnections()
{
    //create new client
    if(m_clients == nullptr)
    {
        m_clients = new client{m_ioservice};
        m_clients->next = nullptr;
    }
    else
    {
        struct client* tmp;
        tmp = new client{m_ioservice};
        tmp->next = m_clients;
        m_clients = tmp;
    }

    m_acceptor->async_accept(m_clients->m_socket,
                             boost::bind(&Server::AcceptHandline, this, m_clients,
                                         boost::asio::placeholders::error));
}

void Server::AcceptHandline(client* current, const boost::system::error_code& error)
{
    if (!error)
    {
        char* name = new char[24];
        current->m_socket.read_some(boost::asio::buffer(name, 24));
        current->m_name = name;
        m_active_connections++;
        std::cout << "New connection under the name: " << name <<
                  "\nCurrently active connections: " << m_active_connections << std::endl;
        delete[] name;
        current->m_socket.async_read_some(boost::asio::buffer(current->m_buffer, m_size_buffer),
                                          boost::bind(&Server::ReadHandline, this, current,
                                                      boost::asio::placeholders::error,
                                                      boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete m_clients;
        m_clients = nullptr;
    }

    AcceptingConnections();
}

void Server::ReadHandline(client* current, const boost::system::error_code& error,
                          size_t bytes_transferred)
{
    if(m_active_connections != 0)
        if(!error)
        {
            char* message = new char[bytes_transferred];

            //adding a name to string
            std::strcpy(message, current->m_name.c_str());
            std::strcpy(&message[current->m_name.length()], ": ");
            std::strcat(message, current->m_buffer);
            //print message for server
            m_gui->ShowNewMessage(message);
            std::cout << message;
            //sending message all clients
            for(client* loop = m_clients; loop != nullptr; loop = loop->next)
                if(loop != current)
                    loop->m_socket.async_write_some(
                            boost::asio::buffer(message, bytes_transferred+current->m_name.length()+1),
                            boost::bind(&Server::WriteHandline, this, loop,
                                        boost::asio::placeholders::error));
            if(!std::strcmp(current->m_buffer, "bye\n"))
            {
                m_active_connections--;
                std::cout << "One of a clients disconnected\nCurrently active connections: "
                << m_active_connections << std::endl;
                current->m_socket.close();
                DeleteOneClient(current);
            }
            else
            {
                //clear buffer
                std::memset(current->m_buffer, 0, m_size_buffer);
                //read current scoket
                current->m_socket.async_read_some(boost::asio::buffer(current->m_buffer, m_size_buffer),
                                                  boost::bind(&Server::ReadHandline, this, current,
                                                              boost::asio::placeholders::error,
                                                              boost::asio::placeholders::bytes_transferred));
            }
            delete[] message;
        }
}

void Server::WriteHandline(client* current, const boost::system::error_code& error)
{
    if(m_active_connections != 0)
        if(!error)
        {
            std::memset(current->m_buffer, 0, m_size_buffer);
            current->m_socket.async_read_some(boost::asio::buffer(current->m_buffer, m_size_buffer),
                                              boost::bind(&Server::ReadHandline, this, current,
                                                          boost::asio::placeholders::error,
                                                          boost::asio::placeholders::bytes_transferred));
        }
}

void Server::DeleteOneClient(client* del)
{
    struct client* tmp = m_clients;
    struct client* buf;
    if(m_clients->next != nullptr)
    {
        while(tmp->next != del)
            tmp = tmp->next;
        buf = tmp->next;
        tmp->next = tmp->next->next;
        delete buf;
    }
    else
    {
        delete m_clients;
        m_clients = nullptr;
    }
}
