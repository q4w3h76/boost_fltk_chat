#include "Window.hpp"
#include <boost/asio/buffer.hpp>
#include <iostream>

Window::Window(char* name, char* ip)
    : m_buffer(new char[m_size_buffer]),
    m_window(new Fl_Window(m_width_window, m_height_window, "Chat")),
    m_io(new IOObject(name, ip)),
    m_send_b(new Fl_Button(5, m_height_window-80, m_width_button*2, m_height_button, "send")),
    m_exit_b(new Fl_Button(m_width_window-m_width_button-5, m_height_window-80, m_width_button, m_height_button, "exit"))
{
    m_window->end();
    m_io->m_input->maximum_size(1024);
    m_exit_b->callback(Window::ExitCallback, this);
    m_io->m_input->callback(Window::SendCallback, m_io);
    m_send_b->callback(Window::SendCallback, m_io);
    m_io->m_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
    m_io->m_input->take_focus();
    m_window->show();

    m_loop_reading = new std::thread(&Window::ReadCallback, this);
}

Window::~Window()
{
    m_io->m_client->SendMessage("bye\n");
    m_loop_reading->detach();
    m_window->hide();
    delete m_loop_reading;
    delete m_buffer;
    delete m_exit_b;
    delete m_send_b;
    delete m_io;
    delete m_window;
}

void Window::SendCallback(Fl_Widget* w, void* arg)
{
    IOObject* io = (IOObject*)arg;
    char* message = new char[1024];
    std::strcpy(message, io->m_input->value());
    std::strcat(message, "\n");
    io->m_client->SendMessage(message);
    delete[] message;

    io->m_output->position(io->m_output->size());
    io->m_output->insert("You: ");
    io->m_output->insert(io->m_input->value());
    io->m_output->insert("\n");

    io->m_input->value("");
    io->m_input->take_focus();
}

void Window::ReadCallback()
{
    while(true)
    {
        std::memset(m_buffer, 0, m_size_buffer);
        m_io->m_client->GetSocket()->read_some(boost::asio::buffer(m_buffer, m_size_buffer));
        m_io->m_output->insert(m_buffer);
        m_io->m_output->insert("\n");
    }
}

void Window::ExitCallback(Fl_Widget* w, void* arg)
{
    Window* window = (Window*)arg;
    delete window;
}
