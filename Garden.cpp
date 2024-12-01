#include "Garden.h"
#include "Snake.h"
#include <QPainter>

class Garden::Private
{
    friend class Garden;

    int width = 32;
    int height = 32;

    int cell  = 10;

    QSize size = QSize(width * cell, height * cell);

    Snake snake = Snake(Snake::Cell(15, 15));
};

Garden::Garden(QWidget *parent)
    : QWidget(parent), p(new Private)
{
    setFixedSize(p->size + QSize(1, 1));
}

Garden::~Garden()
{
}

void Garden::paintEvent(QPaintEvent *event)
{
    QColor background(235, 244, 222);

    QPainter painter(this);
    painter.setBrush(background);
    painter.drawRect(QRect(rect().topLeft(), p->size));

    auto body = p->snake.body();
    for(auto cell : body)
    {
        painter.setBrush(QColor(0, 0, 0));
        painter.drawRect((cell.x) * p->cell,
                         (cell.y) * p->cell,
                         p->cell,
                         p->cell);
    }

    event->accept();
}
