#ifndef BOOST_CHAT_GUI_HPP
#define BOOST_CHAT_GUI_HPP
#include <FL/Fl.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <string>

class GUI {
public:
    GUI();
    ~GUI();
    void Show();
    void ShowNewMessage(std::string msg);
    static void ExitCallback(Fl_Widget* w);
private:
    Fl_Window* m_window;
    Fl_Button* m_exit_b;
    Fl_Multiline_Output* m_output;
    //constant
    enum
    {
        width_window = 400,
        height_window = 600
    };
};


#endif //BOOST_CHAT_GUI_HPP
