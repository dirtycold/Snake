#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QScopedPointer>

class Canvas : public QWidget
{
public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    class Private;
    QScopedPointer<Private> p;
};

#endif // CANVAS_H
