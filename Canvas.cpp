#include "Canvas.h"
#include "Garden.h"
#include "Snake.h"
#include "Apple.h"
#include <QPainter>
#include <QTimer>

class Canvas::Private
{
    friend class Canvas;

    int cell = 10;

    Garden garden = Garden();
    Snake snake = Snake(QPoint(garden.size().width() / 2, garden.size().height() / 2));
    Apple apple = Apple(QPoint(garden.size().width() / 2 + 4, garden.size().height() / 2));

    QTimer timer;
};

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), p(new Private)
{
    setFixedSize(p->garden.size() * p->cell + QSize(1, 1));

    p->timer.setInterval(1000);
    p->timer.setSingleShot(false);
    p->timer.start();

    connect(&p->timer, &QTimer::timeout, this, [this]()
    {
        p->snake.move();
        update();
    });
}

Canvas::~Canvas()
{
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QColor background(224, 224, 224);
    QColor foreground(64, 64, 64);
    QColor highlight = Qt::red;

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

    painter.setBrush(highlight);
    painter.drawRect((p->apple.position().x()) * p->cell,
                     (p->apple.position().y()) * p->cell,
                     p->cell,
                     p->cell);

    event->accept();
}
