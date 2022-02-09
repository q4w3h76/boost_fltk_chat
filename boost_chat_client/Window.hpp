#ifndef BOOST_FLTK_CLIENT_WINDOW_HPP
#define BOOST_FLTK_CLIENT_WINDOW_HPP
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Button.H>
#include <thread>
#include "Client.hpp"

class Window
{
public:
    Window(char* name, char* ip);
    ~Window();
    static void SendCallback(Fl_Widget* w, void* arg);
    void ReadCallback();
    static void ExitCallback(Fl_Widget* w);
private:
    Fl_Window* m_window;
    Fl_Button* m_send_b;
    Fl_Button* m_exit_b;
    std::thread* m_loop_reading;
    char* m_buffer;
    struct IOObject
    {
        Client* m_client;
        Fl_Multiline_Input* m_input;
        Fl_Multiline_Output* m_output;
        IOObject(char* name, char* ip) : m_client(new Client(name, ip)),
                    m_output(new Fl_Multiline_Output(5, 5, m_width_window-10, m_height_window-200)),
                    m_input(new Fl_Multiline_Input(5, m_height_window-190, m_width_window-10, m_height_button*2)) {}
        ~IOObject() { delete m_input; delete m_output; delete m_client; }
    };
    IOObject* m_io;
    //constants
    enum
    {
        m_width_window = 500,
        m_height_window = 600,
        m_width_button = 150,
        m_height_button = 50,
        m_spacing = 150,
        m_size_buffer = 1024
    };
};


#endif //BOOST_FLTK_CLIENT_WINDOW_HPP
