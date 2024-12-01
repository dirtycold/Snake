#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();
};
#endif // WINDOW_H
