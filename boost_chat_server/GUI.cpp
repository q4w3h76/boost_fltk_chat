#include "GUI.hpp"

GUI::GUI()
    : m_window(new Fl_Window(width_window, height_window, "Server")),
      m_exit_b(new Fl_Button(10, height_window-80, width_window-20, 70, "exit")),
      m_output(new Fl_Multiline_Output(10, 10, width_window-20, height_window-100))
{

}

GUI::~GUI()
{
    m_window->hide();
    delete m_output;
    delete m_exit_b;
    delete m_window;
}

void GUI::Show()
{
    m_window->end();
    m_exit_b->callback(GUI::ExitCallback);
    m_window->show();
}

void GUI::ShowNewMessage(std::string msg)
{
    m_output->insert(msg.c_str());
}

void GUI::ExitCallback(Fl_Widget* w)
{
    Fl_Widget* p;
    do
    {
        p = w->parent();
        if(p)
            w = p;
    } while(p);
    w->hide();
}
