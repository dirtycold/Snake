#include "Canvas.h"
#include "Garden.h"
#include "Snake.h"
#include <QPainter>

class Canvas::Private
{
    friend class Canvas;

    int cell = 10;

    Garden garden = Garden();
    Snake snake = Snake(QPoint(15, 15));
};

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), p(new Private)
{
    setFixedSize(p->garden.size() * p->cell + QSize(1, 1));
}

Canvas::~Canvas()
{
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QColor background(235, 244, 222);
    QColor foreground(0, 0, 0);

    QPainter painter(this);
    painter.setBrush(background);
    painter.drawRect(QRect(rect().topLeft(), p->garden.size() * p->cell));

    auto body = p->snake.body();
    for (auto cell : body)
    {
        painter.setBrush(foreground);
        painter.drawRect((cell.x()) * p->cell,
                         (cell.y()) * p->cell,
                         p->cell,
                         p->cell);
    }

    event->accept();
}
