#include "Window.h"
#include "Canvas.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new Canvas);
}

Window::~Window()
{
}

