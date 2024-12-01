#include "Window.h"
#include "Garden.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new Garden);
}

Window::~Window()
{
}

