#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QScopedPointer>

class Canvas : public QWidget
{
public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void step();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // CANVAS_H
